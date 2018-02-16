#include "AssetIndex.h"

#include "assistance/utility.h"

#include <QUrl>

AssetIndex::AssetIndex(QVariant assetIndexVariant) :
	assetIndexVariant_(assetIndexVariant)
{}

QString AssetIndex::id() const
{
	QString mId = value(assetIndexVariant_, "id").toString();
	return mId;
}

int AssetIndex::size() const
{
	int mSize = value(assetIndexVariant_, "size").toInt();
	return mSize;
}

QString AssetIndex::sha1() const
{
	QString mSha1 = value(assetIndexVariant_, "sha1").toString();
	return mSha1;
}

QUrl AssetIndex::url() const
{
	QUrl mUrl = value(assetIndexVariant_, "url").toUrl();
	return mUrl;
}

int AssetIndex::totalSize() const
{
	int mTotalSize = value(assetIndexVariant_, "totalSize").toInt();
	return mTotalSize;
}
