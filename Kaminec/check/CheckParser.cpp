#include "CheckParser.h"

#include "assistance/Path.h"

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
	clientCheckinfo.path_.prepend(Path::versionsPath());
	return clientCheckinfo;
}

QList<CheckInfo> CheckParser::getLibraryCheckInfos() const
{
	auto libraryCheckInfos = checkJson_.getLibraryCheckInfos();
	for(auto& libraryCheckInfo : libraryCheckInfos)
		libraryCheckInfo.path_.prepend(Path::librariesPath() + "/");
	return libraryCheckInfos;
}

CheckInfo CheckParser::getAssetsCheckInfo() const
{
	auto assetsCheckInfo = checkJson_.getAssetsCheckInfo();
	assetsCheckInfo.path_.prepend(Path::assetIndexesPath());
	return assetsCheckInfo;
}

QList<CheckInfo> CheckParser::getAssetObjectsCheckInfos() const
{
	auto assetObjectsCheckInfos = checkAssets_.getAssetObjectsCheckInfos();
	for(auto& assetObjectsCheckInfo : assetObjectsCheckInfos)
		assetObjectsCheckInfo.path_.prepend(Path::assetObjectsPath() + "/");
	return assetObjectsCheckInfos;
}

