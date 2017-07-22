#include "downloadmanagerplus.h"

#include <QFileInfo>
#include <QEventLoop>
#include <QDebug>

DownloadManagerPlus::DownloadManagerPlus(QObject *parent) : QObject(parent)
{
    for(int index = 0; index!= downloadNumber;++index){
        downloaderPool.append(new SingleDownload(this,index));
   }
}

void DownloadManagerPlus::append(const FileItem &item)
{
    
    auto info = item.getInfoList();

    if(item.size==0)
        info.at(2)->setText(QString("unkonwn"));

    downloadQueue.enqueue(item.getDownloadInfo());
    model.appendRow(info);
    itemList.append(info);
    ++totalCount;
    
}

void DownloadManagerPlus::append(QList<FileItem> &itemList)
{
    for(auto &item: itemList)
        append(item);
}

void DownloadManagerPlus::startDownload()
{
    for(int index = 0; index != downloadNumber; index++){
        if(!downloaderPool.at(index).isDownload()&&!downloadQueue.empty()){
            downloaderPool.at(index).start(downloadQueue.dequeue());
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

void DownloadManagerPlus::startNextDownload(int index)
{
    if(downloadQueue.empty()){
        emit finished();
    }
    
    downloaderPool.at(index).start(downloadQueue.dequeue());
}
