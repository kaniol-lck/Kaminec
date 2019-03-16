#include "GameJsonDownload.h"

#include "download/Downloader.h"
#include "assistance/Path.h"

#include <QFileInfo>

GameJsonDownload::GameJsonDownload(QObject *parent, const GameVersion &version) :
	FileDownload(parent),
	version_(version)
{

}

bool GameJsonDownload::exists() const
{
	QFileInfo fileInfo(Path::jsonPath(version_.versionName()));
	return fileInfo.exists() && (fileInfo.size() != 0);
}

void GameJsonDownload::addDownload()
{
	Downloader::instance()->appendDownloadPack(
				DownloadPack(version_.versionName() + " Json Donwload",
							 QList<DownloadInfo>{
								 DownloadInfo(version_.versionName() + ".json",
								 0,
								 Path::jsonPath(version_.versionName()),
								 version_.url(),
								 "Index Json")}),
				[=]{emit downloadFinished();});
}
