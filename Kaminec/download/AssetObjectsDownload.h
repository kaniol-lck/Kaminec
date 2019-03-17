#ifndef ASSETOBJECTSDOWNLOAD_H
#define ASSETOBJECTSDOWNLOAD_H

#include "FileDownload.h"
#include "kits/AssetKit/AssetObject.h"
#include "messenger/DownloadInfo.h"

class AssetObjectsDownload : public FileDownload
{
public:
	AssetObjectsDownload(QObject *parent, const QList<AssetObject> &assetObjects);

	bool exists() const;
	void addDownload();

private:
	QList<AssetObject> assetObjects_;
	QList<DownloadInfo> assetObjectInfos_;

};

#endif // ASSETOBJECTSDOWNLOAD_H
