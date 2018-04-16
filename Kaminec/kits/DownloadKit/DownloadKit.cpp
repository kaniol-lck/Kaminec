#include "downloadkit.h"

#include <QFileInfo>
#include <QEventLoop>
#include <QDebug>

DownloadKit::DownloadKit(QObject *parent) : QObject(parent)
{
	for(int index = 0; index!= downloadNumber_;++index){
		downloaderPool_.append(new SingleDownload(this,&manager_,index));
    }
	model_.setColumnCount(6);
	model_.setHeaderData(0,Qt::Horizontal,"filename");
	model_.setHeaderData(1,Qt::Horizontal,"downloaded size");
	model_.setHeaderData(2,Qt::Horizontal,"total size");
	model_.setHeaderData(3,Qt::Horizontal,"sha1");
	model_.setHeaderData(4,Qt::Horizontal,"path");
	model_.setHeaderData(5,Qt::Horizontal,"url");


	//for each downloader
	for(int index = 0; index != downloadNumber_; index++){
		connect(downloaderPool_.at(index),SIGNAL(finished(int)),SLOT(startNextDownload(int)));
		//once downloader finished and start next download
	}
}

void DownloadKit::append(const FileItem &item)
{

    auto info = item.getInfoList();

	if(item.size_==0)
        info.at(2)->setText(QString("unkonwn"));

	QFileInfo fileInfo(item.path_);
	if(!fileInfo.exists() ||
	   (fileInfo.size() == 0)){
		mutex_.lock();
		downloadQueue_.enqueue(item);
		model_.appendRow(info);
		itemList_.append(info);
		++totalCount_;
		mutex_.unlock();
	}

    startDownload();
}

void DownloadKit::append(QList<FileItem> &itemList)
{
    for(auto &item: itemList)
        append(item);
}

void DownloadKit::startDownload()
{
	//for each downloader
	for(int index = 0; index != downloadNumber_; index++){
		//if downloader is not downloading and download queue is not empty
		if(!downloaderPool_.at(index)->isDownload()&&!downloadQueue_.empty()){
			//add a task to the free downloader
			downloaderPool_.at(index)->start(itemList_.takeFirst(),downloadQueue_.dequeue());
		}
    }
}

int DownloadKit::waitForFinished()
{
    QEventLoop eventloop(this);
    connect(this,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec();
	if(!downloadQueue_.empty()){
        qDebug()<<"exceptional finished.";
        return -1;
    }
    return 0;
}

int DownloadKit::getDownloadedCount()
{
	return downloadedCount_;
}

int DownloadKit::getTotalCount()
{
	return totalCount_;
}

QStandardItemModel *DownloadKit::getModel()
{
	return &model_;
}

void DownloadKit::startNextDownload(int index)
{
    qDebug()<<"downloader "<<index<<" finished,next";
	++downloadedCount_;
	emit downloadedCountChanged(downloadedCount_);

	if(downloadQueue_.empty()){
        bool d = false;
		for(auto downloader: downloaderPool_){
            if(downloader->isDownload()){
                d = true;
                break;
            }
        }
        if(!d){
            qDebug()<<"All finished";
            emit finished();
        }
        return;
	}

	mutex_.lock();
	downloaderPool_.at(index)->start(itemList_.takeFirst(),downloadQueue_.dequeue());
	mutex_.unlock();
}

void DownloadKit::singleFinished(int /*index*/)
{
}
