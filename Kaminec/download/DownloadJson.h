#ifndef DOWNLOADJSON_H
#define DOWNLOADJSON_H

#include "kits/JsonKit/JsonKit.h"
#include "messager/FileItem.h"

#include <QList>

class DownloadJson
{
public:
	DownloadJson(const QString &version);

	QList<FileItem> getLibraryFileItems() const;

	FileItem getAssetsIndexFileItem() const;

	FileItem getClientFileItem() const;

	QString getAssetsIndexId() const;

private:
	JsonKit jsonKit_;
};

#endif // DOWNLOADJSON_H