#include "JsonKit.h"

#include "core/json/main/Library.h"
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

	QByteArray jsonBytes;
	jsonBytes.resize(jsonFile.bytesAvailable());
	jsonBytes = jsonFile.readAll();
	jsonFile.close();

	QJsonParseError ok;
	jsonVariant_ = QJsonDocument::fromJson(jsonBytes, &ok).toVariant();
	if(ok.error != QJsonParseError::NoError){/*something here*/}

	version_ = qMakePair(value(jsonVariant_, "id").toString(),
						 value(jsonVariant_, "inheritsFrom").toString());

	if(version_.second != "")
		inheritedJson_ = std::make_shared<JsonKit>(version_.second);
}

AssetIndex JsonKit::assetIndex() const
{
	if(!assetIndex_){
		if(inheritedJson_)
			assetIndex_ = std::make_shared<AssetIndex>(inheritedJson_->assetIndex());
		else
			assetIndex_ = std::make_shared<AssetIndex>(value(jsonVariant_, "assetIndex"));
	}
	return *assetIndex_;
}

QPair<QString, QString> JsonKit::version() const
{
	return version_;
}

GameCoreJar JsonKit::client() const
{
	if(!gameClient_){
		if(inheritedJson_)
			gameClient_ = std::make_shared<GameCoreJar>(inheritedJson_->client());
		else
			gameClient_ = std::make_shared<GameCoreJar>(value(jsonVariant_, "downloads", "client"));
	}
	return *gameClient_;
}

GameCoreJar JsonKit::server() const
{
	if(!gameServer_){
		if(inheritedJson_)
			gameServer_ = std::make_shared<GameCoreJar>(inheritedJson_->server());
		else
			gameServer_ = std::make_shared<GameCoreJar>(value(jsonVariant_, "downloads", "server"));
	}
	return *gameServer_;
}

QList<Library> JsonKit::libraries() const
{
	if(!libraries_){
		libraries_ = std::make_shared<QList<Library>>();
		for(auto&& libraryVariant : value(jsonVariant_, "libraries").toList())
			libraries_->append(Library(libraryVariant));
	}
	if(inheritedJson_){
		return *libraries_ + inheritedJson_->libraries();
	}
	return *libraries_;
}

QString JsonKit::jarName() const
{
	if(!jarName_){
		if(jsonVariant_.toMap().contains("jar"))
			jarName_ = std::make_shared<QString>(value(jsonVariant_, "jar").toString());
		else
			jarName_ = std::make_shared<QString>(version_.first);
	}
	return *jarName_;
}

QString JsonKit::mainClass() const
{
	if(!mainClass_)
		mainClass_ = std::make_shared<QString>(value(jsonVariant_, "mainClass").toString());
	return *mainClass_;
}

Arguments JsonKit::minecraftArguments() const
{
	if(!minecraftArguments_){
		minecraftArguments_ = std::make_shared<Arguments>(value(jsonVariant_, "minecraftArguments").toString());
	}
	return *minecraftArguments_;
}
