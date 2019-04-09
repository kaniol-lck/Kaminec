#include "GameClientDownload.h"

#include "download/Downloader.h"
#include "assistance/PathReplacer.h"
#include "assistance/Custom.h"

#include <QFileInfo>
#include <QDebug>

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
	auto url = Custom().getUseBMCLAPI()?QString("https://bmclapi2.bangbang93.com/mc/game/%1/client/%2/client.jar").arg(client_.version(), client_.sha1()):
										client_.url();
	qDebug()<<url;
	Downloader::instance()->appendDownloadPack(
				DownloadPack(client_.version() + " Jar Download",
							 QList<DownloadInfo>{
								 DownloadInfo(client_.version() + ".jar",
								 client_.size(),
								 PathReplacer::replace(client_.path()),
								 url,
								 "Game Core File")}),
				[=]{emit downloadFinished();});
}
