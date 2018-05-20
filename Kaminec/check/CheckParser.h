#ifndef CHECKPARSER_H
#define CHECKPARSER_H

#include "messager/Deficiency.h"
#include "check/CheckJson.h"
#include "check/CheckAssets.h"

class CheckParser
{
public:
	CheckParser(QString version);

	Deficiency checkClient();
	QList<Deficiency> checkLibraris();
	Deficiency checkAssetsIndex();
	QList<Deficiency> checkAssetObjects();

private:
	Deficiency checkFile(const CheckInfo &checkInfo) const;

private:
	CheckJson checkJson_;
	CheckAssets checkAssets_;
};

#endif // CHECKPARSER_H
