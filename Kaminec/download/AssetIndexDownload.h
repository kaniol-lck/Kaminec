#ifndef ASSETINDEXDOWNLOAD_H
#define ASSETINDEXDOWNLOAD_H

#include "FileDownload.h"
#include "kits/JsonKit/AssetIndex.h"

class AssetIndexDownload : public FileDownload
{
public:
	explicit AssetIndexDownload(QObject *parent, const AssetIndex &assetIndex);

	bool exists() const;
	void addDownload();

private:
	AssetIndex assetIndex_;
};

#endif // ASSETINDEXDOWNLOAD_H
