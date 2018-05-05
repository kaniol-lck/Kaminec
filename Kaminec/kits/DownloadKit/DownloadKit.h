#ifndef DOWNLOADKIT_H
#define DOWNLOADKIT_H

#include "messager/fileitem.h"
#include "kits/DownloadKit/singledownload.h"

#include <QList>
#include <QQueue>
#include <QMutex>
#include <QStandardItemModel>

#include <QObject>

class DownloadKit : public QObject
{
    Q_OBJECT
public:
	explicit                DownloadKit(QObject *parent = nullptr);

    void                    append(const FileItem &item);
	void                    append(QList<FileItem> &itemList_);
    void                    startDownload();

    int                     waitForFinished();

    int                     getDownloadedCount();
    int                     getTotalCount();

    QStandardItemModel*     getModel();

signals:
    void                    finished();
	void                    downloadedCountChanged(int);

private slots:
    void                    startNextDownload(int index);

public slots:
    void                    singleFinished(int);

private:
	QNetworkAccessManager manager_;
	QQueue<FileItem> downloadQueue_;

	QTime downloadTime_;
	int totalCount_ = 0;
	int downloadedCount_ = 0;

	QStandardItemModel model_;
	QList<QList<QStandardItem*>> itemList_;
	QList<SingleDownload*> downloaderPool_;

	static const int downloadNumber_ = 16;
	QMutex mutex_;
};

#endif // DOWNLOADKIT_H