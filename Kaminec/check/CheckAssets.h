#ifndef CHECKASSETS_H
#define CHECKASSETS_H

#include "messager/CheckInfo.h"
#include "kits/AssetKit/AssetKit.h"

class CheckAssets
{
public:
	explicit CheckAssets(const QString &assetsIndexId);

	QList<CheckInfo> getAssetObjectsCheckInfos();

private:
	AssetKit assetKit_;
};

#endif // CHECKASSETS_H
