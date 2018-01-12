#ifndef GAMEJSON_H
#define GAMEJSON_H

#include "core/json/Library.h"
#include "core/Arguments.h"

#include <memory>
#include <QList>
#include <QPair>

class GameJson
{
public:
	GameJson(QString version);

	QString getGameJarPath();

	QStringList getLibraryPaths() const;

	QStringList getExtractPaths() const;

	QString getMainClass() const;

	Arguments getGameArguments() const;

	QString getAssetsIndex() const;

private:
	std::shared_ptr<GameJson> inheritsFromJson;

	QList<Library> libraries;

	//the first is current index
	//the second is it inherited from
	QPair<QString, QString> versionIndex;

	QString jarName;

	QString mainClass;
	Arguments gameArguments;
	QString assetsIndex;
};

#endif // GAMEJSON_H
