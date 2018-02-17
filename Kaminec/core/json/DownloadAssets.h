#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include "messager/fileitem.h"
#include "core/json/AssetsKit.h"

#include <QList>
#include <QJsonObject>

class DownloadAssets
{
public:
	explicit DownloadAssets(QString assetsIndexId);

	QList<FileItem> getDownloadAssetsUrls();

private:
	static QString kResourcesDownload;

	AssetsKit assetsKit_;
	QVariant assets_;
	QString corePath_;
};

#endif // ASSETSMANAGER_H
