#include "DownloadAssets.h"

#include "core/Path.h"
#include "assistance/utility.h"

QString DownloadAssets::kResourcesDownload = "http://resources.download.minecraft.net/";

DownloadAssets::DownloadAssets(const QString &assetsIndexId) :
	assetsKit_(assetsIndexId),
	corePath_(Path::corePath())
{

}

QList<FileItem> DownloadAssets::getDownloadAssetsUrls()
{
	QList<FileItem> downloadAssetsUrls;
	for(const auto& object : assetsKit_.objects()){
		downloadAssetsUrls.append(FileItem(object.name(),
										   object.size(),
										   "NULL",
										   object.path(),
										   kResourcesDownload + object.url()));
	}
	return downloadAssetsUrls;
}
