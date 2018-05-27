#include "DownloadParser.h"

#include "assistance/Path.h"

#include <cassert>

DownloadParser::DownloadParser(const QVariantList versionList, int index) :
	versionList_(versionList),
	index_(index)
{}

DownloadInfo DownloadParser::gameJsonDownloadInfo() const
{
	return DownloadInfo(QString("%1.json").arg(versionList_.at(index_).toMap().value("id").toString()),
						0,
						QString("%1/%2/%2.json")
						.arg(Path::versionsPath()).arg(versionList_.at(index_).toMap().value("id").toString()),
						versionList_.at(index_).toMap().value("url").toUrl()
						);
}

void DownloadParser::loadGameJson()
{
	downloadJson_ = std::make_shared<DownloadJson>(versionList_.at(index_).toMap().value("id").toString());
}

DownloadInfo DownloadParser::clientDownloadInfo() const
{
	assert(downloadJson_);
	auto downloadInfo = downloadJson_->getClientDownloadInfo();
	downloadInfo.path_.prepend(Path::versionsPath());
	return downloadInfo;
}

QList<DownloadInfo> DownloadParser::libraryDownloadInfos() const
{
	assert(downloadJson_);
	auto downloadInfos = downloadJson_->getLibraryDownloadInfos();
	for(auto& downloadInfo : downloadInfos)
		downloadInfo.path_.prepend(Path::librariesPath() + "/");
	return downloadInfos;
}

DownloadInfo DownloadParser::assetIndexDownloadInfo() const
{
	assert(downloadJson_);
	auto downloadInfo = downloadJson_->getAssetsIndexDownloadInfo();
	downloadInfo.path_.prepend(Path::assetIndexesPath());
	return downloadInfo;
}

void DownloadParser::loadAssetIndex()
{
	assert(downloadJson_);
	downloadAssets_ = std::make_shared<DownloadAssets>(downloadJson_->getAssetsIndexId());
}

QList<DownloadInfo> DownloadParser::assetObjectDownloadInfos() const
{
	assert(downloadAssets_);
	auto downloadInfos = downloadAssets_->getAssetObjectsDownloadInfos();
	for(auto& downloadInfo : downloadInfos)
		downloadInfo.path_.prepend(Path::assetObjectsPath() + "/");
	return downloadInfos;
}
