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
        if(!downloaderPool.at(index)->isDownload()&&!downloadQueue.empty()){
            downloaderPool.at(index)->start(itemList.takeFirst(),downloadQueue.dequeue());
            connect(downloaderPool.at(index),SIGNAL(finished(int)),SLOT(startNextDownload(int)));
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
    qDebug()<<"next";
    if(downloadQueue.empty()){
        emit finished();
        return;
    }

    downloaderPool.at(index)->start(itemList.takeFirst(),downloadQueue.dequeue());
}

void DownloadManagerPlus::singleFinished(int index)
{
    if(downloadQueue.empty())
        return;

    downloaderPool.at(index)->start(itemList.takeFirst(),downloadQueue.dequeue());
}
