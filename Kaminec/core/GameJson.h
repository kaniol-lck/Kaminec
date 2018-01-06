#ifndef GAMEJSON_H
#define GAMEJSON_H

#include "core/Library.h"
#include "core/Arguements.h"

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

	Arguements getGameArguements() const;

	QString getAssetsIndex() const;

private:
	std::shared_ptr<GameJson> inheritsFromJson;

	QList<Library> libraries;

	//the first is current index
	//the second is it inherited from
	QPair<QString, QString> versionIndex;

	QString jarName;

	QString mainClass;
	Arguements gameArguements;
	QString assetsIndex;
};

#endif // GAMEJSON_H
