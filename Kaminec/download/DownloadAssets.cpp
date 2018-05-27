#include "DownloadAssets.h"

#include "assistance/utility.h"

QString DownloadAssets::kResourcesDownload = "http://resources.download.minecraft.net/";

DownloadAssets::DownloadAssets(const QString &assetsIndexId) :
	assetKit_(assetsIndexId)
{}

QList<DownloadInfo> DownloadAssets::getAssetObjectsDownloadInfos()
{
	QList<DownloadInfo> assetsDownloadInfos;
	for(const auto& object : assetKit_.assetObjects()){
		assetsDownloadInfos.append(DownloadInfo(object.name(),
										   object.size(),
										   object.path(),
										   kResourcesDownload + object.url()));
	}
	return assetsDownloadInfos;
}
