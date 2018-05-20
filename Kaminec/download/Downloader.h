#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "download/DownloadJson.h"
#include "download/DownloadAssets.h"
#include "kits/DownloadKit/DownloadKit.h"

#include <QObject>
#include <QStandardItemModel>
#include <QTemporaryFile>

class Downloader : public QObject
{
	Q_OBJECT
public:
	explicit Downloader(QObject *parent = nullptr);
	void init();

	QStandardItemModel* getVersionsModel();
	QStandardItemModel* getDownloadModel();

	int getTotalCount();

	void download(int index);

signals:
	void downloadedCountChanged(int);
	void finished();

public slots:

private:
	static QString kVersionManifestDownlaod;

	bool inited_ = false;
	QStandardItemModel model_;
	QString tempFileName_;
	QTemporaryFile tempVersionsFile_;
	DownloadKit *downloadKit_;
	DownloadJson *downloadJson_;
	DownloadAssets *downloadAsset_;
	QVariantList versionList_;
	int totalCount_;
};

#endif // DOWNLOADER_H
