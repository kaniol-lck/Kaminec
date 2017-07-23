#include "DownloadManager.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QStandardItemModel>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>

DownloadManager::DownloadManager(QObject *parent):
    QObject(parent),
    downloadedCount(0),
    totalCount(0),
    model(),
    itemList()
{
    model.setColumnCount(6);
    model.setHeaderData(0,Qt::Horizontal,"filename");
    model.setHeaderData(1,Qt::Horizontal,"downloaded size");
    model.setHeaderData(2,Qt::Horizontal,"total size");
    model.setHeaderData(3,Qt::Horizontal,"sha1");
    model.setHeaderData(4,Qt::Horizontal,"path");
    model.setHeaderData(5,Qt::Horizontal,"url");
}

void DownloadManager::append(const QPair<QUrl, QString> &url)
{
    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SLOT(startNextDownload()));

    QList<QStandardItem *> info = FileItem(url).getInfoList();
    downloadQueue.enqueue(url);
    model.appendRow(info);
    itemList.append(info);
    ++totalCount;
}

void DownloadManager::append(const QList<QPair<QUrl, QString> > &urlList)
{
    for(QPair<QUrl, QString> url: urlList)
        append(url);

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SIGNAL(finished()));
}

int DownloadManager::append(const FileItem &item)
{
    QFileInfo fileInfo(item.mPath);
    if(fileInfo.exists()&&fileInfo.size()==item.mSize){
        emit finished();
        return 1;
    }

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SLOT(startNextDownload()));

    auto info = item.getInfoList();

    if(item.mSize==0)
        info.at(2)->setText(QString("unkonwn"));

    downloadQueue.enqueue(item.getDownloadInfo());
    model.appendRow(info);
    itemList.append(info);
    ++totalCount;
    return 0;
}

int DownloadManager::append(QList<FileItem> &itemList)
{
    int dld=0;
    for(auto item: itemList){
        if(append(item)!=1)
            dld=0;
    }

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SIGNAL(finished()));

    return dld;
}

#include <QEventLoop>
int DownloadManager::waitForFinished()
{
    QEventLoop eventLoop(this);
    connect(this,SIGNAL(finished()),&eventLoop,SLOT(quit()));
    eventLoop.exec();
    if(!downloadQueue.empty()){
        qDebug()<<"exceptionally finished";
        return -1;
    }
    return 0;
}

int DownloadManager::getDownloadedCount()
{
    return downloadedCount;
}

int DownloadManager::getTotalCount()
{
    return totalCount;
}

QStandardItemModel *DownloadManager::getModel()
{
    return &model;
}


void DownloadManager::startNextDownload()
{
    if (downloadQueue.isEmpty()) {
        printf("%d/%d files downloaded successfully\n", downloadedCount, totalCount);
        emit finished();
        return;
    }

    auto url = downloadQueue.dequeue();
    QString filename = url.second;//!
    QDir d = QFileInfo(filename).path();
    if(!d.exists())
        d.mkpath(d.path());
    if(output.exists())
        output.remove();
    output.setFileName(filename);
    if (!output.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
                qPrintable(filename), url.first.toEncoded().constData(),
                qPrintable(output.errorString()));

        startNextDownload();
        return;                 // skip this download
    }

    QNetworkRequest request(url.first);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));

    // prepare the output
    printf("Downloading %s...\n", url.first.toEncoded().constData());
    downloadTime.start();
}

void DownloadManager::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    itemList.at(0).at(1)->setText(QString::number(bytesReceived));
    if(itemList.at(0).at(2)->text()=="0")
        itemList.at(0).at(2)->setText(QString::number(bytesTotal));
    qDebug()<<QString("%1%  %2/%3").arg(bytesTotal==0?0:bytesReceived*100/bytesTotal,3).arg(bytesReceived,6).arg(bytesTotal,6);
}

void DownloadManager::downloadFinished()
{
    output.close();

    if (currentDownload->error()) {
        // download failed
        qDebug()<<"Failed:"<<qPrintable(currentDownload->errorString())<<"\n";
        QMessageBox::warning(static_cast<QWidget*>(parent()),"Download Failed",QString(currentDownload->errorString()));
    } else {
        printf("Succeeded.\n");
        ++downloadedCount;
        emit downloadedCountChanged(downloadedCount);

        model.removeRow(0);
        for(auto p:itemList.at(0))
            delete p;
        itemList.removeFirst();
    }

    currentDownload->deleteLater();
    startNextDownload();
}

void DownloadManager::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}
