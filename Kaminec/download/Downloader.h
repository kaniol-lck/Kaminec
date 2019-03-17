#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "kits/DownloadKit/DownloadKit.h"

#include <QObject>
#include <QStandardItemModel>

class Downloader : public QObject
{
	Q_OBJECT
private:
	explicit Downloader(QObject *parent = nullptr);
	Downloader() = delete;
	Downloader(Downloader&) = delete;

public:
	static void init(QObject *parent);
	static Downloader *instance();

	QStandardItemModel* getModel();

	void appendDownloadPack(const DownloadPack &downloadPack);
	void appendDownloadPack(const DownloadPack &downloadPack, std::function<void()> slotFuntion);

	enum Column { FileName, FileType, Status };
	enum StatusType { Waiting, Downloading, Finished };

	static QList<QStandardItem *> info2items(const DownloadInfo &downloadInfo);
	static QMap<QString, Downloader::StatusType> downloadPack2map(const DownloadPack &downloadPack);

private:
	DownloadKit downloadKit_;
	QMap<QString, QMap<QString, StatusType>> downloadStatus_;
	QMap<QString, QList<QStandardItem *>> downloadPackItems_;
	QMap<QString, QMap<QString, QList<QStandardItem *>>> downloadItems_;
	QStandardItemModel model_;
	QMap<QString, std::function<void()>> slotFunctions_;

	static Downloader *pInstance;
};

#endif // DOWNLOADER_H
