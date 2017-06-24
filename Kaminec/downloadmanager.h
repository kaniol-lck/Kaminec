#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QFile>
#include <QObject>
#include <QQueue>
#include <QTime>
#include <QPair>
#include <QUrl>
#include <QNetworkAccessManager>

class downloadManager: public QObject
{
    Q_OBJECT
public:
    downloadManager(QObject *parent = 0);

    void append(const QPair<QUrl,QString> &url);
    void append(const QList<QPair<QUrl,QString>> &urlList);
    int waitForFinished();

signals:
    void finished();

private slots:
    void startNextDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    QNetworkAccessManager manager;
    QQueue<QPair<QUrl,QString>> downloadQueue;
    QNetworkReply *currentDownload;
    QFile output;
    QTime downloadTime;

    int downloadedCount;
    int totalCount;
};

#endif
