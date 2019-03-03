#include "VersionManifestDownload.h"

#include "kits/DownloadKit/Downloadkit.h"
#include "assistance/PathReplacer.h"

VersionManifestDownload::VersionManifestDownload(QObject *parent) : QObject(parent)
{}

void VersionManifestDownload::AddDownload()
{
	DownloadKit::instance()->appendDownloadPack(
				DownloadPack("Version Manifest",
							 QList<DownloadInfo>{
								 DownloadInfo("version_manifest.json",
								 0,
								 PathReplacer::replace("<launcher>/version_manifest.json"),
								 QUrl("https://launchermeta.mojang.com/mc/game/version_manifest.json"),
								 "Manifest")}),
				[=]{emit downloadFinished();});
}
