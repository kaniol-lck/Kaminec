#include "CheckParser.h"

#include <QFile>
#include <QCryptographicHash>

CheckParser::CheckParser(QString version) :
	checkJson_(version),
	checkAssets_(checkJson_.getAssetsIndexId())
{}

Deficiency CheckParser::checkClient()
{
	return checkFile(checkJson_.getClientCheckInfo());
}

QList<Deficiency> CheckParser::checkLibraris()
{
	QList<Deficiency> libraryDeficiencies;

	for(const auto& checkInfo : checkJson_.getLibraryCheckInfos()){
		auto libraryDeficiency = checkFile(checkInfo);
		if(!libraryDeficiency.ok_)
			libraryDeficiencies << libraryDeficiency;
	}

	return libraryDeficiencies;
}

Deficiency CheckParser::checkAssetsIndex()
{
	return checkFile(checkJson_.getAssetsCheckInfo());
}

QList<Deficiency> CheckParser::checkAssetObjects()
{
	QList<Deficiency> assetObjectsDeficiencies;

	for(const auto& checkInfo : checkAssets_.getAssetObjectsCheckInfos()){
		auto assetObjectsDeficiency = checkFile(checkInfo);
		if(!assetObjectsDeficiency.ok_)
			assetObjectsDeficiencies << assetObjectsDeficiency;
	}

	return assetObjectsDeficiencies;
}

Deficiency CheckParser::checkFile(const CheckInfo &checkInfo) const
{
	QFile file(checkInfo.fileName_);

	if(!file.exists())
		return Deficiency(checkInfo, Deficiency::NotExist);

	if(!file.open(QIODevice::ReadOnly))
		return Deficiency(checkInfo, Deficiency::OpenError);

	if(QCryptographicHash::hash(file.readAll(), checkInfo.checkCodeType_) != checkInfo.checkCode_)
		return Deficiency(checkInfo, Deficiency::WrongCheckCode);

	return Deficiency(true);
}
