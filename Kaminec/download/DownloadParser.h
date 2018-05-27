#ifndef DOWNLOADPARSER_H
#define DOWNLOADPARSER_H

#include "download/DownloadJson.h"
#include "download/DownloadAssets.h"

#include <memory>

class DownloadParser
{
public:
	DownloadParser(const QVariantList versionList, int index);

	DownloadInfo gameJsonDownloadInfo() const;

	void loadGameJson();

	DownloadInfo clientDownloadInfo() const;
	QList<DownloadInfo> libraryDownloadInfos() const;

	DownloadInfo assetIndexDownloadInfo() const;
	void loadAssetIndex();

	QList<DownloadInfo> assetObjectDownloadInfos() const;

private:
	QVariantList versionList_;
	int index_;
	std::shared_ptr<DownloadJson> downloadJson_;
	std::shared_ptr<DownloadAssets> downloadAssets_;
};

#endif // DOWNLOADPARSER_H
