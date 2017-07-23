#include "singledownload.h"
#include "fileitem.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


SingleDownload::SingleDownload(QObject *parent, QNetworkAccessManager *manager, int index):
    QObject(parent),
    pManager(manager),
    output(new QFile(this)),
    mIndex(index)
{

}

bool SingleDownload::isDownload() const
{
    return mIsdownload;
}

void SingleDownload::start(QList<QStandardItem*> modelItem, FileItem fileItem)
{
    mModelItem = modelItem;
    QString filename = fileItem.mPath;
    QDir dir = QFileInfo(filename).path();
    if(!dir.exists())
        dir.mkpath(dir.path());
    if(output->exists())
        output->remove();
    output->setFileName(filename);
    if(!output->open(QIODevice::WriteOnly)){
        qDebug()<<"Open "<<filename<<" failed";
        emit finished(mIndex);
        return;
    }

    QNetworkRequest request(fileItem.mUrl);
    currentDownload = pManager->get(request);
    connect(currentDownload,SIGNAL(downloadProgress(qint64,qint64)),SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload,SIGNAL(finished()),SLOT(downloadFinished()));
    connect(currentDownload,SIGNAL(readyRead()),SLOT(downloadReadyRead()));

    qDebug()<<"Downloading "<<fileItem.mUrl;
    mIsdownload = true;
}

void SingleDownload::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if(mIsdownload){
        qDebug()<<mIsdownload;
        mModelItem.at(1)->setText(QString::number(bytesReceived));
        if(mModelItem.at(2)->text()=="0")
            mModelItem.at(2)->setText(QString::number(bytesTotal));
    }

    qDebug()<<QString("%1%  %2/%3").arg(bytesTotal==0?0:bytesReceived*100/bytesTotal,3).arg(bytesReceived,6).arg(bytesTotal,6);
}

void SingleDownload::downloadReadyRead()
{
    output->write(currentDownload->readAll());
}

void SingleDownload::downloadFinished()
{
    output->close();
    mIsdownload = false;

    if(currentDownload->error()){
        qDebug()<<"Failed:"<<currentDownload->errorString();
    }else {
        qDebug()<<"Succeed.";
        emit finished(mIndex);
    }

}
