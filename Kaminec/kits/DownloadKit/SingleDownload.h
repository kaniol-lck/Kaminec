#ifndef SINGLEDOWNLOAD_H
#define SINGLEDOWNLOAD_H

#include "messenger/DownloadInfo.h"

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
	explicit SingleDownload(QObject *parent, QNetworkAccessManager *manager);

	bool isOccupied() const;

	void start(const DownloadInfo &downloadInfo, const QList<QStandardItem *> &modelItem);

signals:
	void finished(int row) const;

private:
	QNetworkAccessManager *manager_;
	QNetworkReply *currentDownload_;
	QFile *output_;

	QList<QStandardItem*> modelItem_;
	bool isOccupied_ = false;
};

#endif // SINGLEDOWNLOAD_H
