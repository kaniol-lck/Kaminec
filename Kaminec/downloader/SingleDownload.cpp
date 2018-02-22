#include "singledownload.h"
#include "messager/fileitem.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
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

void SingleDownload::start(const QList<QStandardItem *> &modelItem, const FileItem &fileItem)
{
    modelItem_ = modelItem;
    QString filename = fileItem.path_;
	QDir dir = QFileInfo(filename).path();
    if(!dir.exists())
		dir.mkpath(dir.path());
    output_->setFileName(filename);
	if(!output_->open(QIODevice::ReadWrite)){
        emit finished(index_);
		throw std::runtime_error(QString("Could not open File(%1)").arg(output_->fileName()).toStdString());
        return;
    }
	qDebug()<<"Start download:"<<output_->fileName();

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
        modelItem_.at(1)->setText(QString::number(bytesReceived));
        if(modelItem_.at(2)->text()=="0")
            modelItem_.at(2)->setText(QString::number(bytesTotal));
    }

}

void SingleDownload::downloadReadyRead()
{
    if(output_->isWritable()){
        output_->write(currentDownload_->readAll());
    }
}

void SingleDownload::downloadFinished()
{
    output_->close();

    qDebug()<<"downloader "<<index_<<" finished downloading file:"<<output_->fileName();
    qDebug()<<modelItem_.at(0)->text()<<" from "<<modelItem_.at(5)->text();

    isdownload_ = false;

    if(currentDownload_->error()){
		throw std::runtime_error(QString("Download Error:").append(currentDownload_->errorString()).toStdString());
	}else {
        qDebug()<<"Succeed:"<<output_->fileName();
        emit finished(index_);
    }

}
