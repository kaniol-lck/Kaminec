#include "singledownload.h"
#include "messager/DownloadInfo.h"
#include "assistance/Exceptions.hpp"

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

void SingleDownload::start(const QList<QStandardItem *> &modelItem, const DownloadInfo &downloadInfo)
{
    modelItem_ = modelItem;
    QString filename = downloadInfo.path_;
	QDir dir = QFileInfo(filename).path();
    if(!dir.exists())
		dir.mkpath(dir.path());
    output_->setFileName(filename);
	if(!output_->open(QIODevice::ReadWrite)){
        emit finished(index_);
		throw FileOpenException(output_->fileName());
        return;
    }
	qDebug()<<"Start download:"<<output_->fileName();

    QNetworkRequest request(downloadInfo.url_);
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
	qDebug()<<modelItem_.at(0)->text()<<" from "<<modelItem_.at(4)->text();

    isdownload_ = false;

    if(currentDownload_->error()){
		throw DownloadException(currentDownload_->errorString());
	}else {
        qDebug()<<"Succeed:"<<output_->fileName();
        emit finished(index_);
	}
}
