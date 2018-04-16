#ifndef ASSETSKIT_H
#define ASSETSKIT_H

#include "kits/AssetKit/AssetObject.h"

#include <memory>
#include <QVariant>
#include <QList>

class AssetKit
{
public:
	AssetKit(const QString &assetIndexId);

	QList<AssetObject> assetObjects();

private:
	QVariant assetsVariant_;

	mutable std::shared_ptr<QList<AssetObject>> assetObjects_;

};

#endif // ASSETSKIT_H
