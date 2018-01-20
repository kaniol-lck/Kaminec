#include "AssetIndex.h"

#include "assistance/utility.h"

#include <QUrl>

AssetIndex::AssetIndex(QVariant assetIndexVariant) :
	mAssetIndexVariant(assetIndexVariant)
{}

QString AssetIndex::id() const
{
	static QString mId = value(mAssetIndexVariant, "id").toString();
	return mId;
}

int AssetIndex::size() const
{
	static int mSize = value(mAssetIndexVariant, "size").toInt();
	return mSize;
}

QString AssetIndex::sha1() const
{
	static QString mSha1 = value(mAssetIndexVariant, "sha1").toString();
	return mSha1;
}

QUrl AssetIndex::url() const
{
	static QUrl mUrl = value(mAssetIndexVariant, "url").toUrl();
	return mUrl;
}

int AssetIndex::totalSize() const
{
	static int mTotalSize = value(mAssetIndexVariant, "totalSize").toInt();
	return mTotalSize;
}
