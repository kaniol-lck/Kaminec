#include "AssetIndex.h"

#include "assistance/utility.h"

#include <QUrl>

AssetIndex::AssetIndex(QVariant assetIndexVariant) :
	assetIndexVariant_(assetIndexVariant)
{}

QString AssetIndex::id() const
{
	static QString mId = value(assetIndexVariant_, "id").toString();
	return mId;
}

int AssetIndex::size() const
{
	static int mSize = value(assetIndexVariant_, "size").toInt();
	return mSize;
}

QString AssetIndex::sha1() const
{
	static QString mSha1 = value(assetIndexVariant_, "sha1").toString();
	return mSha1;
}

QUrl AssetIndex::url() const
{
	static QUrl mUrl = value(assetIndexVariant_, "url").toUrl();
	return mUrl;
}

int AssetIndex::totalSize() const
{
	static int mTotalSize = value(assetIndexVariant_, "totalSize").toInt();
	return mTotalSize;
}
