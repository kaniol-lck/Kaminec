#include "JsonKit.h"

#include "core/json/Library.h"
#include "core/Path.h"
#include "assistance/utility.h"

#include <memory>
#include <QDir>
#include <QJsonDocument>
#include <QDebug>

JsonKit::JsonKit(QString version)
{
	QFile jsonFile(Path::getJsonPath(version));


	//open json file and parse
	if(!jsonFile.exists()){/*something here*/}
	if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){/*something here*/}

	QByteArray jsonByte;
	jsonByte.resize(jsonFile.bytesAvailable());
	jsonByte = jsonFile.readAll();
	jsonFile.close();

	QJsonParseError ok;
	jsonVariant = QJsonDocument::fromJson(jsonByte, &ok).toVariant();
	if(ok.error != QJsonParseError::NoError){/*something here*/}

	mVersion = qMakePair(value(jsonVariant, "id").toString(),
						 value(jsonVariant, "inheritsFrom").toString());

	if(mVersion.second != "")
		inheritedJson = std::make_shared<JsonKit>(mVersion.second);
}

AssetIndex JsonKit::assetIndex() const
{
	if(!mAssetIndex){
		if(inheritedJson)
			mAssetIndex = std::make_shared<AssetIndex>(inheritedJson->assetIndex());
		else
			mAssetIndex = std::make_shared<AssetIndex>(value(jsonVariant, "assetIndex"));
	}
	return *mAssetIndex;
}

QPair<QString, QString> JsonKit::version() const
{
	return mVersion;
}

GameCoreJar JsonKit::client() const
{
	if(!mGameClient){
		if(inheritedJson)
			mGameClient = std::make_shared<GameCoreJar>(inheritedJson->client());
		else
			mGameClient = std::make_shared<GameCoreJar>(value(jsonVariant, "downloads", "client"));
	}
	return *mGameClient;
}

GameCoreJar JsonKit::server() const
{
	if(!mGameServer){
		if(inheritedJson)
			mGameServer = std::make_shared<GameCoreJar>(inheritedJson->server());
		else
			mGameServer = std::make_shared<GameCoreJar>(value(jsonVariant, "downloads", "server"));
	}
	return *mGameServer;
}

QList<Library> JsonKit::libraries() const
{
	if(!mLibraries){
		mLibraries = std::make_shared<QList<Library>>();
		for(auto&& libraryVariant : value(jsonVariant, "libraries").toList())
			mLibraries->append(Library(libraryVariant));
	}
	if(inheritedJson){
		return *mLibraries + inheritedJson->libraries();
	}
	return *mLibraries;
}

QString JsonKit::jarName() const
{
	if(!mJarName){
		if(jsonVariant.toMap().contains("jar"))
			mJarName = std::make_shared<QString>(value(jsonVariant, "jar").toString());
		else
			mJarName = std::make_shared<QString>(mVersion.first);
	}
	return *mJarName;
}

QString JsonKit::mainClass() const
{
	if(!mMainClass)
		mMainClass = std::make_shared<QString>(value(jsonVariant, "mainClass").toString());
	return *mMainClass;
}

Arguments JsonKit::minecraftArguments() const
{
	if(!mMinecraftArguments){
		mMinecraftArguments = std::make_shared<Arguments>(value(jsonVariant, "minecraftArguments").toString());
	}
	return *mMinecraftArguments;
}
