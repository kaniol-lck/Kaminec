#ifndef DOWNLOADASSETS_H
#define DOWNLOADASSETS_H

#include "messenger/DownloadInfo.h"
#include "kits/AssetKit/AssetKit.h"

#include <QList>
#include <QVariant>

class DownloadAssets
{
public:
	explicit DownloadAssets(const QString &assetsIndexId);

	QList<DownloadInfo> getAssetObjectsDownloadInfos();

private:
	static QString kResourcesDownload;

	AssetKit assetKit_;
};

#endif // DOWNLOADASSETS_H
