#include "GameLibrariesDownload.h"

#include "download/Downloader.h"
#include "assistance/PathReplacer.h"

#include <QFileInfo>

GameLibrariesDownload::GameLibrariesDownload(QObject *parent, const QList<Library> &libraries) :
	FileDownload(parent),
	libraries_(libraries)
{
	for(const auto &libraray : libraries){
		QFileInfo fileInfo(PathReplacer::replace(libraray.path()));
		if((!fileInfo.exists()) || (fileInfo.size() != libraray.size()))
			libraryInfos_ << DownloadInfo(libraray.fileName(),
										  libraray.size(),
										  PathReplacer::replace(libraray.path()),
										  libraray.url(),
										  "Game Library File");
	}
}

bool GameLibrariesDownload::exists() const
{
	return libraryInfos_.isEmpty();
}

void GameLibrariesDownload::addDownload()
{
	Downloader::instance()->appendDownloadPack(
				DownloadPack("Libraries Download",
							 libraryInfos_),
				[=]{emit downloadFinished();});
}
