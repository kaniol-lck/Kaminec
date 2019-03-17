#include "SingleDownload.h"
#include "messenger/DownloadInfo.h"
#include "exception/Exceptions.hpp"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>


SingleDownload::SingleDownload(QObject *parent, QNetworkAccessManager *manager):
    QObject(parent),
    manager_(manager),
	output_(new QFile(this))
{

}

bool SingleDownload::isOccupied() const
{
	return isOccupied_;
}

void SingleDownload::start(const QPair<QString, DownloadInfo> &downloadInfo)
{
	packName_ = downloadInfo.first;
	fileName_ = downloadInfo.second.name();
	QString filename = downloadInfo.second.path();
	QDir dir = QFileInfo(filename).path();
    if(!dir.exists())
		dir.mkpath(dir.path());
    output_->setFileName(filename);
	if(!output_->open(QIODevice::ReadWrite)){
		emit finished(packName_, fileName_);
		throw FileOpenException(output_->fileName());
    }
	qDebug()<<"Start download:"<<output_->fileName();

	QNetworkRequest request(downloadInfo.second.url());
    currentDownload_ = manager_->get(request);

	connect(currentDownload_, &QNetworkReply::finished, this, [&]{
		output_->close();
		emit finished(packName_, fileName_);

//		qDebug()<<modelItem_.at(0)->text()<<" from "<<modelItem_.at(4)->text();

		isOccupied_ = false;

		if(currentDownload_->error()){
			throw DownloadException(currentDownload_->errorString());
		}else {
			qDebug()<<"Succeed:"<<output_->fileName();
		}
	});

	connect(currentDownload_, &QNetworkReply::readyRead, this, [&]{
		if(output_->isWritable())
			output_->write(currentDownload_->readAll());
	});

	isOccupied_ = true;
}
