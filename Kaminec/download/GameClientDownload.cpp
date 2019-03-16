#include "GameClientDownload.h"

#include "download/Downloader.h"
#include "assistance/PathReplacer.h"

#include <QFileInfo>

GameClientDownload::GameClientDownload(QObject *parent, const GameCoreJar &client) :
	FileDownload(parent),
	client_(client)
{}

bool GameClientDownload::exists() const
{
	QFileInfo fileInfo(PathReplacer::replace(client_.path()));
	return fileInfo.exists() && (fileInfo.size() == client_.size());
}

void GameClientDownload::addDownload()
{
	Downloader::instance()->appendDownloadPack(
				DownloadPack(client_.version() + " Jar Download",
							 QList<DownloadInfo>{
								 DownloadInfo(client_.version() + ".jar",
								 client_.size(),
								 PathReplacer::replace(client_.path()),
								 client_.url(),
								 "Game Core File")}),
				[=]{emit downloadFinished();});
}
