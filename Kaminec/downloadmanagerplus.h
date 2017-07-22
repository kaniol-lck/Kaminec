#ifndef DOWNLOADMANAGERPLUS_H
#define DOWNLOADMANAGERPLUS_H

#include "fileitem.h"
#include "singledownload.h"

#include <QList>
#include <QQueue>
#include <QStandardItemModel>

#include <QObject>

class DownloadManagerPlus : public QObject
{
    Q_OBJECT
public:
    explicit                DownloadManagerPlus(QObject *parent = nullptr);

    void                    append(const FileItem &item);
    void                    append(QList<FileItem>& itemList);
    void                    startDownload();

    int                     waitForFinished();

    int                     getDownloadedCount();
    int                     getTotalCount();

    QStandardItemModel*     getModel();

signals:
    void                    finished();

private slots:
    void                    startNextDownload(int index);

public slots:
    void                    singleFinished(int);

private:
    QNetworkAccessManager manager;
    QQueue<FileItem> downloadQueue;

    QTime downloadTime;
    int totalCount;
    int downloadedCount;

    QStandardItemModel model;
    QList<QList<QStandardItem*>> itemList;
    QList<SingleDownload*> downloaderPool;

    static const int downloadNumber = 5;
};

#endif // DOWNLOADMANAGERPLUS_H
