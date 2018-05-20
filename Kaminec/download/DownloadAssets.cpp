#include "DownloadAssets.h"

#include "assistance/utility.h"

QString DownloadAssets::kResourcesDownload = "http://resources.download.minecraft.net/";

DownloadAssets::DownloadAssets(const QString &assetsIndexId) :
	assetKit_(assetsIndexId)
{}

QList<DownloadInfo> DownloadAssets::getAssetsDownloadInfos()
{
	QList<DownloadInfo> assetsDownloadInfos;
	for(const auto& object : assetKit_.assetObjects()){
		assetsDownloadInfos.append(DownloadInfo(object.name(),
										   object.size(),
										   "NULL",
										   object.path(),
										   kResourcesDownload + object.url()));
	}
	return assetsDownloadInfos;
}
