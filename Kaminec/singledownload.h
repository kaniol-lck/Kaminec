#ifndef SINGLEDOWNLOAD_H
#define SINGLEDOWNLOAD_H

#include "fileitem.h"

#include <QObject>
#include <QList>
#include <QStandardItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class SingleDownload : public QObject
{
    Q_OBJECT
public:
    explicit SingleDownload(QObject *parent, QList<QStandardItem*> modelItem, QNetworkAccessManager *manager,int index);

    bool isDownload() const;

    void start(FileItem fileItem);

signals:
    void finished(int) const;
//    int downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadReadyRead();
    void downloadFinished();

public slots:

private:
    QNetworkAccessManager *pManager;
    QNetworkReply *currentDownload;
    QFile *output;

    QList<QStandardItem*> mModelItem;
    bool mIsdownload;
    int mIndex;
};

#endif // SINGLEDOWNLOAD_H
