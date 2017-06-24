#include "downloadManager.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>

downloadManager::downloadManager(QObject *parent)
    : QObject(parent), downloadedCount(0), totalCount(0)
{
}

void downloadManager::append(const QList<QPair<QUrl, QString> > &urlList)
{
    for(QPair<QUrl, QString> url: urlList)
        append(url);

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SIGNAL(finished()));
}

#include <QEventLoop>
int downloadManager::waitForFinished()
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

void downloadManager::append(const QPair<QUrl, QString> &url)
{
    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SLOT(startNextDownload()));

    downloadQueue.enqueue(url);
    ++totalCount;
}

void downloadManager::startNextDownload()
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

void downloadManager::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug()<<QString("%1%  %2/%3").arg(bytesTotal==0?0:bytesReceived*100/bytesTotal,3).arg(bytesReceived,6).arg(bytesTotal,6);
}

void downloadManager::downloadFinished()
{
    //progressBar.clear();//!
    output.close();

    if (currentDownload->error()) {
        // download failed
        qDebug()<<"Failed:"<<qPrintable(currentDownload->errorString())<<"\n";
    } else {
        printf("Succeeded.\n");
        ++downloadedCount;
    }

    currentDownload->deleteLater();
    startNextDownload();
}

void downloadManager::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}
