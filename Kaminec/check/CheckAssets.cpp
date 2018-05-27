#include "CheckAssets.h"

CheckAssets::CheckAssets(const QString &assetsIndexId) :
	assetKit_(assetsIndexId)
{}

QList<CheckInfo> CheckAssets::getAssetObjectsCheckInfos() const
{
	QList<CheckInfo> assetObjectsCheckInfos;
	for(const auto& object : assetKit_.assetObjects()){
		assetObjectsCheckInfos.append(CheckInfo(object.name(),
												object.size(),
												QCryptographicHash::Sha1,
												object.hash(),
												object.path(),
												object.url()));
	}
	return assetObjectsCheckInfos;
}
