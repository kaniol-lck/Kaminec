#include "AssetIndex.h"

#include "assistance/utility.h"

#include <QUrl>

AssetIndex::AssetIndex(QVariant assetIndexVariant) :
	assetIndexVariant_(assetIndexVariant)
{}

QString AssetIndex::id() const
{
	return value(assetIndexVariant_, "id").toString();
}

int AssetIndex::size() const
{
	return value(assetIndexVariant_, "size").toInt();
}

QString AssetIndex::sha1() const
{
	return value(assetIndexVariant_, "sha1").toString();
}

QUrl AssetIndex::url() const
{
	return value(assetIndexVariant_, "url").toUrl();
}

int AssetIndex::totalSize() const
{
	return value(assetIndexVariant_, "totalSize").toInt();
}
