#ifndef DOWNLOADJSON_H
#define DOWNLOADJSON_H

#include "core/json/JsonKit.h"
#include "messager/FileItem.h"

#include <QList>

class DownloadJson : public JsonKit
{
public:
	DownloadJson(QString version);

	QList<FileItem> getLibraryFileItems();

	FileItem getAssetsJsonFileItem();

	FileItem getClientFileItem();
};

#endif // DOWNLOADJSON_H
