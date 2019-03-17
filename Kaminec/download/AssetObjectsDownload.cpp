#include "AssetObjectsDownload.h"

#include "download/Downloader.h"
#include "assistance/PathReplacer.h"

#include <QFileInfo>

AssetObjectsDownload::AssetObjectsDownload(QObject *parent, const QList<AssetObject> &assetObjects) :
	FileDownload(parent),
	assetObjects_(assetObjects)
{
	for(const auto &assetObject : assetObjects){
		QFileInfo fileInfo(PathReplacer::replace(assetObject.path()));
		if((!fileInfo.exists()) || (fileInfo.size() != assetObject.size()))
			assetObjectInfos_ << DownloadInfo(assetObject.name(),
										  assetObject.size(),
										  PathReplacer::replace(assetObject.path()),
										  QString("http://resources.download.minecraft.net/") + assetObject.url(),
										  tr("Game Asset File"));
	}
}

bool AssetObjectsDownload::exists() const
{
	return assetObjectInfos_.isEmpty();
}

void AssetObjectsDownload::addDownload()
{
	Downloader::instance()->appendDownloadPack(
				DownloadPack(tr("Asset Objects Download"),
							 assetObjectInfos_),
				[=]{emit downloadFinished();});
}
