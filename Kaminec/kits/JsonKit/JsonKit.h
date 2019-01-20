#ifndef JSONKIT_H
#define JSONKIT_H

#include "kits/JsonKit/Library.h"
#include "messenger/Arguments.h"
#include "kits/JsonKit/AssetIndex.h"
#include "kits/JsonKit/GameCoreJar.h"

#include <memory>
#include <QList>
#include <QPair>

class JsonKit
{
public:
	JsonKit(const QString &version);

	AssetIndex assetIndex() const;

	QPair<QString, QString> version() const;

	GameCoreJar client() const;

	GameCoreJar server() const;

	QList<Library> libraries() const;

	QString jarPath() const;

	QString mainClass() const;

	Arguments minecraftArguments() const;

	Arguments JVMArguments() const;

	QStringList versionChain() const;

private:
	QVariant jsonVariant_;

	//the first is current version
	//the second is whom it inherits from
	QPair<QString, QString> version_;

	bool needJar_;

	std::shared_ptr<JsonKit> inheritedJson_;

	//all these members uses lazy fetching.
	//coz it's not so cheap to convert

	mutable std::shared_ptr<AssetIndex> assetIndex_;

	mutable std::shared_ptr<GameCoreJar> gameClient_;

	mutable std::shared_ptr<GameCoreJar> gameServer_;

	mutable std::shared_ptr<QList<Library>> libraries_;

	mutable std::shared_ptr<QString> jarName_;

	/*logging*/

	mutable std::shared_ptr<QString> mainClass_;

	mutable std::shared_ptr<Arguments> minecraftArguments_;

	mutable std::shared_ptr<Arguments> JVMArguments_;

};

#endif // JSONKIT_H
