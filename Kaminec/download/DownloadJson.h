#ifndef DOWNLOADJSON_H
#define DOWNLOADJSON_H

#include "kits/JsonKit/JsonKit.h"
#include "messager/DownloadInfo.h"

#include <QList>

class DownloadJson
{
public:
	explicit DownloadJson(const QString &version);

	QList<DownloadInfo> getLibraryDownloadInfos() const;

	DownloadInfo getAssetsIndexDownloadInfo() const;

	DownloadInfo getClientDownloadInfo() const;

	QString getAssetsIndexId() const;

private:
	JsonKit jsonKit_;
};

#endif // DOWNLOADJSON_H
