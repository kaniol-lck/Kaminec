#include "DownloadAssets.h"

#include "assistance/utility.h"

QString DownloadAssets::kResourcesDownload = "http://resources.download.minecraft.net/";

DownloadAssets::DownloadAssets(const QString &assetsIndexId) :
	assetsKit_(assetsIndexId)
{}

QList<FileItem> DownloadAssets::getDownloadAssetsUrls()
{
	QList<FileItem> downloadAssetsUrls;
	for(const auto& object : assetsKit_.assetObjects()){
		downloadAssetsUrls.append(FileItem(object.name(),
										   object.size(),
										   "NULL",
										   object.path(),
										   kResourcesDownload + object.url()));
	}
	return downloadAssetsUrls;
}