#ifndef DOWNLOADASSETS_H
#define DOWNLOADASSETS_H

#include "messager/fileitem.h"
#include "core/json/assets/AssetsKit.h"

#include <QList>
#include <QVariant>

class DownloadAssets
{
public:
	explicit DownloadAssets(const QString &assetsIndexId);

	QList<FileItem> getDownloadAssetsUrls();

private:
	static QString kResourcesDownload;

	AssetsKit assetsKit_;
	QVariant assets_;
};

#endif // DOWNLOADASSETS_H
