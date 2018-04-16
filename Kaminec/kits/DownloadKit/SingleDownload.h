#ifndef SINGLEDOWNLOAD_H
#define SINGLEDOWNLOAD_H

#include "messager/fileitem.h"

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
    explicit SingleDownload(QObject *parent,QNetworkAccessManager *manager,int index);

    bool isDownload() const;

	void start(const QList<QStandardItem *> &modelItem, const FileItem &fileItem);

signals:
    void finished(int) const;

private slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadReadyRead();
    void downloadFinished();

public slots:

private:
	QNetworkAccessManager *manager_;
	QNetworkReply *currentDownload_;
	QFile *output_;

	QList<QStandardItem*> modelItem_;
	bool isdownload_ = false;
	int index_;
};

#endif // SINGLEDOWNLOAD_H
