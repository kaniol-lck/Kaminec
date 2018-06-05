#include "CheckParser.h"

#include "assistance/PathReplacer.h"

CheckParser::CheckParser(QString version) :
	checkJson_(version),
	checkAssets_(checkJson_.getAssetsIndexId())
{}

QList<CheckInfo> CheckParser::getCheckInfos()
{
	QList<CheckInfo> checkInfos;
	checkInfos << getClientCheckInfo();
	checkInfos << getLibraryCheckInfos();
	checkInfos << getAssetsCheckInfo();
	checkInfos << getAssetObjectsCheckInfos();
	return checkInfos;
}

CheckInfo CheckParser::getClientCheckInfo() const
{
	auto clientCheckinfo = checkJson_.getClientCheckInfo();
	PathReplacer::replace(clientCheckinfo.path_);
	return clientCheckinfo;
}

QList<CheckInfo> CheckParser::getLibraryCheckInfos() const
{
	auto libraryCheckInfos = checkJson_.getLibraryCheckInfos();
	for(auto& libraryCheckInfo : libraryCheckInfos)
		PathReplacer::replace(libraryCheckInfo.path_);
	return libraryCheckInfos;
}

CheckInfo CheckParser::getAssetsCheckInfo() const
{
	auto assetsCheckInfo = checkJson_.getAssetsCheckInfo();
	PathReplacer::replace(assetsCheckInfo.path_);
	return assetsCheckInfo;
}

QList<CheckInfo> CheckParser::getAssetObjectsCheckInfos() const
{
	auto assetObjectsCheckInfos = checkAssets_.getAssetObjectsCheckInfos();
	for(auto& assetObjectsCheckInfo : assetObjectsCheckInfos)
		PathReplacer::replace(assetObjectsCheckInfo.path_);
	return assetObjectsCheckInfos;
}

