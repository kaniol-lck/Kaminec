#include "DownloadKit.h"

#include "kits/DownloadKit/SingleDownload.h"

#include <QFileInfo>
#include <QEventLoop>
#include <QDebug>

DownloadKit::DownloadKit(QObject *parent) : QObject(parent)
{
	for(int index = 0; index!= downloadNumber_; ++index){
		downloaderPool_.append(new SingleDownload(this,&manager_));
		connect(downloaderPool_.at(index), &SingleDownload::finished, this, &DownloadKit::singleFinished);
		//once downloader finished and start next download
	}
}

void DownloadKit::appendDownloadFile(const QString &packName, const DownloadInfo &downloadInfo)
{
	QFileInfo fileInfo(downloadInfo.path());
	//download only if file does not exist or has empty size(download failed)
	if(fileInfo.exists() && (fileInfo.size() != 0))
		return;
	downloadInfoQueue_.enqueue(qMakePair(packName, downloadInfo));
	spur();
}

void DownloadKit::spur()
{
	for(auto singleDownloader : downloaderPool_){
		if(downloadInfoQueue_.isEmpty()) break;
		if(!singleDownloader->isOccupied()){
			auto info = downloadInfoQueue_.dequeue();
			emit started(info.first, info.second.name());
			singleDownloader->start(info);
		}
	}
}

void DownloadKit::singleFinished(const QString &packName, const QString &fileName)
{
	qDebug()<<"downloader finished,next";
	emit finished(packName, fileName);

	if(downloadInfoQueue_.empty()){
		bool noTask = true;
		for(auto downloader: downloaderPool_){
			if(downloader->isOccupied()){
				noTask = false;
				break;
			}
		}
		if(noTask){
			qDebug()<<"All finished.";
		}
		return;
	}
	spur();
}
