#include "VersionManifestDownload.h"

#include "download/Downloader.h"
#include "assistance/PathReplacer.h"

#include <QDebug>
#include <QFileInfo>

VersionManifestDownload::VersionManifestDownload(QObject *parent, QString fileName) :
	FileDownload(parent),
	fileName_(fileName)
{}

bool VersionManifestDownload::exists() const
{
	QFileInfo fileInfo(PathReplacer::replace(fileName_));
	return fileInfo.exists() && (fileInfo.size() != 0);
}

void VersionManifestDownload::addDownload()
{
	Downloader::instance()->appendDownloadPack(
				DownloadPack("Version Manifest",
							 QList<DownloadInfo>{
								 DownloadInfo("version_manifest.json",
								 0,
								 PathReplacer::replace(fileName_),
								 QUrl("https://launchermeta.mojang.com/mc/game/version_manifest.json"),
								 "Manifest")}),
				[=]{emit downloadFinished();});
}
