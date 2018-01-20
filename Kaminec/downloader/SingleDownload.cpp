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
    manager_(manager),
    output_(new QFile(this)),
    index_(index)
{

}

bool SingleDownload::isDownload() const
{
    return isdownload_;
}

void SingleDownload::start(QList<QStandardItem*> modelItem, FileItem fileItem)
{
    modelItem_ = modelItem;
    QString filename = fileItem.path_;
    QDir dir = QFileInfo(filename).path();
//    qDebug()<<dir;
    if(!dir.exists())
        dir.mkpath(dir.path());
//    if(fileItem.mSize!=0&&output->size()!=fileItem.mSize)
//        output->remove();
    output_->setFileName(filename);
    if(!output_->open(QIODevice::ReadWrite)){
        qDebug()<<"Open "<<filename<<" failed";
        emit finished(index_);
        return;
    }
    qDebug()<<"Start download:"<<output_->fileName();
//    QProcess::execute("touch "+fileItem.mPath);
//    qDebug()<<output->isOpen();

    QNetworkRequest request(fileItem.url_);
    currentDownload_ = manager_->get(request);
    connect(currentDownload_,SIGNAL(downloadProgress(qint64,qint64)),SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload_,SIGNAL(finished()),SLOT(downloadFinished()));
    connect(currentDownload_,SIGNAL(readyRead()),SLOT(downloadReadyRead()));

    isdownload_ = true;
}

void SingleDownload::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if(isdownload_){
//        qDebug()<<mIsdownload;
        modelItem_.at(1)->setText(QString::number(bytesReceived));
        if(modelItem_.at(2)->text()=="0")
            modelItem_.at(2)->setText(QString::number(bytesTotal));
    }

//    qDebug()<<QString("%1%  %2/%3").arg(bytesTotal==0?0:bytesReceived*100/bytesTotal,3).arg(bytesReceived,6).arg(bytesTotal,6);
}

void SingleDownload::downloadReadyRead()
{
//    qDebug()<<output->fileName()<<" is writable? "<<output->isWritable();
    if(output_->isWritable()){
        output_->write(currentDownload_->readAll());
    }
//    qDebug()<<output->readAll();
}

void SingleDownload::downloadFinished()
{
//    qDebug()<<output->readAll();
    output_->close();

    qDebug()<<"downloader "<<index_<<" finished downloading file:"<<output_->fileName();
    qDebug()<<modelItem_.at(0)->text()<<" from "<<modelItem_.at(5)->text();

    isdownload_ = false;

    if(currentDownload_->error()){
        qDebug()<<"Failed:"<<currentDownload_->errorString();
    }else {
        qDebug()<<"Succeed:"<<output_->fileName();
        emit finished(index_);
    }

}
