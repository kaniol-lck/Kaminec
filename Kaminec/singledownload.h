#ifndef SINGLEDOWNLOAD_H
#define SINGLEDOWNLOAD_H

#include "fileitem.h"

#include <QObject>
#include <QNetworkReply>
#include <QFile>

class SingleDownload : public QObject
{
    Q_OBJECT
public:
    explicit SingleDownload(QObject *parent,int index);

    bool isDownload() const;

    void start(FileItem) const;

signals:
    void finished(int);
    int downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private slots:
    void downloadReadyRead();

public slots:

private:
    QNetworkReply *currentDownload;
    QFile *output;

    int mIndex;
};

#endif // SINGLEDOWNLOAD_H
