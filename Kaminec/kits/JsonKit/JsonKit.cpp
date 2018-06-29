#include "JsonKit.h"

#include "assistance/Path.h"
#include "assistance/utility.h"
#include "assistance/Exceptions.hpp"

#include <stdexcept>
#include <QJsonDocument>

JsonKit::JsonKit(const QString &version)
{
	QFile jsonFile(Path::getJsonPath(version));

	//open json file and parse
	if(!jsonFile.exists())
		throw FileNotFoundException(jsonFile.fileName());
	if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
		throw FileOpenException(jsonFile.fileName());

	QByteArray jsonBytes;
	jsonBytes.resize(jsonFile.bytesAvailable());
	jsonBytes = jsonFile.readAll();
	jsonFile.close();

	QJsonParseError ok;
	jsonVariant_ = QJsonDocument::fromJson(jsonBytes, &ok).toVariant();
	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(jsonFile.fileName(), ok.errorString(), true);

	needJar_ = jsonVariant_.toMap().contains("jar");

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
		if(needJar_)
			gameClient_ = std::make_shared<GameCoreJar>(inheritedJson_->client());//Is the content of inheritsFrom the same as jar?
		else
			gameClient_ = std::make_shared<GameCoreJar>(value(jsonVariant_, "downloads", "client"), version_.first);
	}
	return *gameClient_;
}

GameCoreJar JsonKit::server() const
{
	if(!gameServer_){
		if(inheritedJson_)
			gameServer_ = std::make_shared<GameCoreJar>(inheritedJson_->server());
		else
			gameServer_ = std::make_shared<GameCoreJar>(value(jsonVariant_, "downloads", "server"), version_.first);
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

QString JsonKit::mainClass() const
{
	if(!mainClass_)
		mainClass_ = std::make_shared<QString>(value(jsonVariant_, "mainClass").toString());
	return *mainClass_;
}

Arguments JsonKit::minecraftArguments() const
{
	if(!minecraftArguments_){
		if(jsonVariant_.toMap().contains("arguments") &&
		   value(jsonVariant_, "arguments").toMap().contains("game")){
			minecraftArguments_ = std::make_shared<Arguments>(value(jsonVariant_, "arguments", "game"));
		}
		else {
			minecraftArguments_ = std::make_shared<Arguments>(value(jsonVariant_, "minecraftArguments").toString());
		}
	}
	return *minecraftArguments_;
}

Arguments JsonKit::JVMArguments() const
{
	if(!JVMArguments_){
			minecraftArguments_ = std::make_shared<Arguments>(value(jsonVariant_, "arguments", "jvm").toStringList());
	}
	return *JVMArguments_;
}

QStringList JsonKit::versionChain() const
{
	QStringList versionList;
	versionList.append(version_.first);
	if(inheritedJson_)
		versionList.append(inheritedJson_->versionChain());

	return versionList;
}
