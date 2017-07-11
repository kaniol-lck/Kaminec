#ifndef DownloadManager_H
#define DownloadManager_H

#include "fileitem.h"

#include <QFile>
#include <QObject>
#include <QQueue>
#include <QTime>
#include <QPair>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QStandardItemModel>

class DownloadManager: public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = 0);

    void append(const QPair<QUrl, QString>& url);
    void append(const QList<QPair<QUrl,QString>> &urlList);
    void append(const FileItem &item);
    void append(QList<FileItem>& itemList);
    int waitForFinished();
    int getDownloadedCount();
    int getTotalCount();

    QStandardItemModel* getModel();

signals:
    void finished();
    void downloadedCountChanged(int);

private slots:
    void startNextDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    QNetworkAccessManager manager;
    QQueue<QPair<QUrl,QString>> downloadQueue;
    QPair<QUrl,QString> currentDownloadQueue;
    QNetworkReply * currentDownload;
    QFile output;
    QTime downloadTime;

    int downloadedCount;
    int totalCount;

    QStandardItemModel model;
    QList<QList<QStandardItem *>> itemList;
};

#endif
