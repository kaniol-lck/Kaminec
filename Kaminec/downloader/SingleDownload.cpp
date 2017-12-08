#include "singledownload.h"
#include "messager/fileitem.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
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
//    qDebug()<<dir;
    if(!dir.exists())
        dir.mkpath(dir.path());
//    if(fileItem.mSize!=0&&output->size()!=fileItem.mSize)
//        output->remove();
    output->setFileName(filename);
    if(!output->open(QIODevice::ReadWrite)){
        qDebug()<<"Open "<<filename<<" failed";
        emit finished(mIndex);
        return;
    }
    qDebug()<<"Start download:"<<output->fileName();
//    QProcess::execute("touch "+fileItem.mPath);
//    qDebug()<<output->isOpen();

    QNetworkRequest request(fileItem.mUrl);
    currentDownload = pManager->get(request);
    connect(currentDownload,SIGNAL(downloadProgress(qint64,qint64)),SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload,SIGNAL(finished()),SLOT(downloadFinished()));
    connect(currentDownload,SIGNAL(readyRead()),SLOT(downloadReadyRead()));

    mIsdownload = true;
}

void SingleDownload::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if(mIsdownload){
//        qDebug()<<mIsdownload;
        mModelItem.at(1)->setText(QString::number(bytesReceived));
        if(mModelItem.at(2)->text()=="0")
            mModelItem.at(2)->setText(QString::number(bytesTotal));
    }

//    qDebug()<<QString("%1%  %2/%3").arg(bytesTotal==0?0:bytesReceived*100/bytesTotal,3).arg(bytesReceived,6).arg(bytesTotal,6);
}

void SingleDownload::downloadReadyRead()
{
//    qDebug()<<output->fileName()<<" is writable? "<<output->isWritable();
    if(output->isWritable()){
        output->write(currentDownload->readAll());
    }
//    qDebug()<<output->readAll();
}

void SingleDownload::downloadFinished()
{
//    qDebug()<<output->readAll();
    output->close();

    qDebug()<<"downloader "<<mIndex<<" finished downloading file:"<<output->fileName();
    qDebug()<<mModelItem.at(0)->text()<<" from "<<mModelItem.at(5)->text();

    mIsdownload = false;

    if(currentDownload->error()){
        qDebug()<<"Failed:"<<currentDownload->errorString();
    }else {
        qDebug()<<"Succeed:"<<output->fileName();
        emit finished(mIndex);
    }

}
