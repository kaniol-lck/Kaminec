#ifndef GAMEJSON_H
#define GAMEJSON_H

#include "core/json/Library.h"
#include "core/Arguments.h"
#include "core/json/AssetIndex.h"
#include "core/json/GameCoreJar.h"

#include <memory>
#include <QList>
#include <QPair>

class JsonKit
{
public:
	JsonKit(QString version);

	AssetIndex assetIndex() const;

	QPair<QString, QString> version() const;

	GameCoreJar client() const;

	GameCoreJar server() const;

	QList<Library> libraries() const;

	QString jarName() const;

	QString mainClass() const;

	Arguments minecraftArguments() const;

private:
	QVariant jsonVariant;

	//the first is current version
	//the second is whom it inherits from
	QPair<QString, QString> mVersion;

	std::shared_ptr<JsonKit> inheritedJson;

	//all these members uses lazy fetching.
	//coz it's not so cheap to convert

	mutable std::shared_ptr<AssetIndex> mAssetIndex;

	mutable std::shared_ptr<GameCoreJar> mGameClient;

	mutable std::shared_ptr<GameCoreJar> mGameServer;

	mutable std::shared_ptr<QList<Library>> mLibraries;

	mutable std::shared_ptr<QString> mJarName;

	/*logging*/

	mutable std::shared_ptr<QString> mMainClass;

	mutable std::shared_ptr<Arguments> mMinecraftArguments;

};

#endif // GAMEJSON_H
