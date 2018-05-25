#ifndef CHECKPARSER_H
#define CHECKPARSER_H

#include "messager/Deficiency.h"
#include "check/CheckJson.h"
#include "check/CheckAssets.h"

class CheckParser
{
public:
	CheckParser(QString version);

	QList<CheckInfo> getCheckInfos();

private:
	CheckInfo getClientCheckInfo() const;
	QList<CheckInfo> getLibraryCheckInfos() const;
	CheckInfo getAssetsCheckInfo() const;
	QList<CheckInfo> getAssetObjectsCheckInfos() const;

private:
	CheckJson checkJson_;
	CheckAssets checkAssets_;
};

#endif // CHECKPARSER_H
