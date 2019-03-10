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

	static QList<QStandardItem *> downloadPack2items(const DownloadPack &downloadPack);
	static QMap<QString, bool> downloadPack2map(const DownloadPack &downloadPack);

	enum Column { FileName, FileType, Status };

private:
	DownloadKit downloadKit_;
	QMap<QString, QMap<QString, bool>> downloadStatus_;
	QStandardItemModel model_;
	QMap<QString, std::function<void()>> slotFunctions_;

	static Downloader *pInstance;
};

#endif // DOWNLOADER_H
