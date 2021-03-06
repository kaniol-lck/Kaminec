#ifndef CHECKASSETS_H
#define CHECKASSETS_H

#include "messenger/CheckInfo.h"
#include "kits/AssetKit/AssetKit.h"

class CheckAssets
{
public:
	explicit CheckAssets(const QString &assetsIndexId);

	QList<CheckInfo> getAssetObjectsCheckInfos() const;

private:
	AssetKit assetKit_;
};

#endif // CHECKASSETS_H
