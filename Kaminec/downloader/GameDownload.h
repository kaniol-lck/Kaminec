#ifndef GAMEDOWNLOAD_H
#define GAMEDOWNLOAD_H

#include "core/json/DownloadJson.h"
#include "core/json/AssetsManager.h"
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
	bool inited = false;
	QString corePath;
	QStandardItemModel model;
	QString tempFileName;
	QTemporaryFile tempVersionsFile;
	DownloadManagerPlus *downloadManagerPlus;
	DownloadJson *downloadJson;
	AssetsManager *downloadAsset;
	QVariantList versionList;
	int totalCount;
};

#endif // GAMEDOWNLOAD_H
