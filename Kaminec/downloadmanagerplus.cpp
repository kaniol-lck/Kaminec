#include "downloadmanagerplus.h"

#include <QFileInfo>
#include <QEventLoop>
#include <QDebug>

DownloadManagerPlus::DownloadManagerPlus(QObject *parent) : QObject(parent)
{
    for(int index = 0; index!= downloadNumber;++index){
        downloaderPool.append(new SingleDownload(this,&manager,index));
    }
    model.setColumnCount(6);
    model.setHeaderData(0,Qt::Horizontal,"filename");
    model.setHeaderData(1,Qt::Horizontal,"downloaded size");
    model.setHeaderData(2,Qt::Horizontal,"total size");
    model.setHeaderData(3,Qt::Horizontal,"sha1");
    model.setHeaderData(4,Qt::Horizontal,"path");
    model.setHeaderData(5,Qt::Horizontal,"url");
}

void DownloadManagerPlus::append(const FileItem &item)
{

    auto info = item.getInfoList();

    if(item.mSize==0)
        info.at(2)->setText(QString("unkonwn"));

	QFileInfo fileInfo(item.mPath);
	if(fileInfo.exists() &&
	   (fileInfo.size() != 0))
		return;

    downloadQueue.enqueue(item.getDownloadInfo());
    model.appendRow(info);
    itemList.append(info);
    ++totalCount;

    startDownload();
}

void DownloadManagerPlus::append(QList<FileItem> &itemList)
{
    for(auto &item: itemList)
        append(item);
}

void DownloadManagerPlus::startDownload()
{
	//for each downloader
    for(int index = 0; index != downloadNumber; index++){
		//if downloader is not downloading and download queue is not empty
        if(!downloaderPool.at(index)->isDownload()&&!downloadQueue.empty()){
			//add a task to the free downloader
            downloaderPool.at(index)->start(itemList.takeFirst(),downloadQueue.dequeue());
			//once downloader finished and start next download
            connect(downloaderPool.at(index),SIGNAL(finished(int)),SLOT(startNextDownload(int)));
//            connect(downloaderPool.at(index),SIGNAL(finished(int)),SLOT(singleFinished(int)));
        }
    }
}

int DownloadManagerPlus::waitForFinished()
{
    QEventLoop eventloop(this);
    connect(this,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec();
    if(!downloadQueue.empty()){
        qDebug()<<"exceptional finished.";
        return -1;
    }
    return 0;
}

int DownloadManagerPlus::getDownloadedCount()
{
    return downloadedCount;
}

int DownloadManagerPlus::getTotalCount()
{
    return totalCount;
}

QStandardItemModel *DownloadManagerPlus::getModel()
{
    return &model;
}

void DownloadManagerPlus::startNextDownload(int index)
{
    if(model.rowCount()!=0){
//        model.removeRow(0);//!!!!!!!!!
    }
    qDebug()<<"downloader "<<index<<" finished,next";
	++downloadedCount;
	emit downloadedCountChanged(downloadedCount);
    if(downloadQueue.empty()){
        bool d = false;
        for(auto downloader: downloaderPool){
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

    downloaderPool.at(index)->start(itemList.takeFirst(),downloadQueue.dequeue());
}

void DownloadManagerPlus::singleFinished(int /*index*/)
{
}
