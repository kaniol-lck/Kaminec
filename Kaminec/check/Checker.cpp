#include "Checker.h"

#include "check/CheckParser.h"

#include <QDebug>

Checker::Checker(QObject *parent) :
	QObject(parent)
{}

QList<Deficiency> Checker::check(const QString &version)
{
	QList<Deficiency> deficiencies;
	CheckParser checkParser(version);
	auto checkInfos = checkParser.getCheckInfos();
	for(const auto& checkInfo : checkInfos){
		auto deficiency = checkFile(checkInfo);
		if(!deficiency.ok_)
			deficiencies << deficiency;
	}
	return deficiencies;
}



Deficiency Checker::checkFile(const CheckInfo &checkInfo)
{
	QFile file(checkInfo.path_);

	if(!file.exists())
		return Deficiency(checkInfo, Deficiency::NotExist);

	if(!file.open(QIODevice::ReadOnly))
		return Deficiency(checkInfo, Deficiency::OpenError);

	if(QCryptographicHash::hash(file.readAll(), checkInfo.checkCodeType_).toHex() != checkInfo.checkCode_)
		return Deficiency(checkInfo, Deficiency::WrongCheckCode);

	return Deficiency(true);
}
