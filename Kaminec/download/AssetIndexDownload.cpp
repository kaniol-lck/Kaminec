#include "AssetIndexDownload.h"

#include "download/Downloader.h"
#include "assistance/Path.h"

#include <QFileInfo>

AssetIndexDownload::AssetIndexDownload(QObject *parent, const AssetIndex &assetIndex) :
	FileDownload(parent),
	assetIndex_(assetIndex)
{}

bool AssetIndexDownload::exists() const
{
	QFileInfo fileInfo(Path::assetIndexPath(assetIndex_.id()));
	return fileInfo.exists() && (fileInfo.size() != assetIndex_.size());
}

void AssetIndexDownload::addDownload()
{
	Downloader::instance()->appendDownloadPack(
				DownloadPack(assetIndex_.id() + " Json Donwload",
							 QList<DownloadInfo>{
								 DownloadInfo(assetIndex_.id() + ".json",
								 assetIndex_.size(),
								 Path::assetIndexPath(assetIndex_.id()),
								 assetIndex_.url(),
								 "Asset Index Json")}),
				[=]{emit downloadFinished();});
}
