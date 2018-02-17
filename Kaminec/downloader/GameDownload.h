#ifndef GAMEDOWNLOAD_H
#define GAMEDOWNLOAD_H

#include "core/json/main/DownloadJson.h"
#include "core/json/assets/DownloadAssets.h"
#include "downloader/downloadmanagerplus.h"

#include <QObject>
#include <QStandardItemModel>
#include <QTemporaryFile>

class GameDownload : public QObject
{
	Q_OBJECT
public:
	explicit GameDownload(QObject *parent = nullptr);
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
	QString corePath_;
	QStandardItemModel model_;
	QString tempFileName_;
	QTemporaryFile tempVersionsFile_;
	DownloadManagerPlus *downloadManagerPlus_;
	DownloadJson *downloadJson_;
	DownloadAssets *downloadAsset_;
	QVariantList versionList_;
	int totalCount_;
};

#endif // GAMEDOWNLOAD_H
