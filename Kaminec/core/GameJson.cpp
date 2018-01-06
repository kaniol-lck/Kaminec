#include "GameJson.h"

#include "core/Library.h"
#include "core/Path.h"
#include "assistance/utility.h"

#include <QDir>
#include <QJsonDocument>
#include <QDebug>

GameJson::GameJson(QString version)
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
	auto jsonVar = QJsonDocument::fromJson(jsonByte, &ok).toVariant();
	if(ok.error != QJsonParseError::NoError){/*something here*/}

	//infomation collection

	for(auto&& libraryVar : value(jsonVar, "libraries").toList())
		libraries << Library(libraryVar);

	mainClass = value(jsonVar, "mainClass").toString();

	versionIndex = qMakePair(value(jsonVar, "id").toString(),
							 value(jsonVar, "inheritsFrom").toString());

	if(jsonVar.toMap().contains("jar")){
		jarName = value(jsonVar, "jar").toString();
	} else{
		jarName = versionIndex.first;
	}
	gameArguements = Arguements(value(jsonVar, "minecraftArguments").toString());

	assetsIndex = value(jsonVar, "assets").toString();

	//initialize inheritJson
	if(versionIndex.second != "")
		inheritsFromJson = std::make_shared<GameJson>(versionIndex.second);

}

QString GameJson::getGameJarPath()
{
	return QString("/%1/%1.jar").arg(jarName);
}

QStringList GameJson::getLibraryPaths() const
{
	QStringList librariesPaths;
	for(const auto& library : libraries){
		if(library.isNatives()) continue;//ignore extract file
		librariesPaths << library.path();
	}
	if(inheritsFromJson){
		//append libraries in the inheritsFrom json
		librariesPaths << inheritsFromJson->getLibraryPaths();
	}

	return librariesPaths;
}

QStringList GameJson::getExtractPaths() const
{
	QStringList librariesPaths;
	for(const auto& library : libraries){
		if(library.isNatives())
			librariesPaths << library.path();//keep extract file only
	}
	if(inheritsFromJson){
		//append extract files in the inheritsFrom json
		librariesPaths << inheritsFromJson->getExtractPaths();
	}

	return librariesPaths;
}

QString GameJson::getMainClass() const
{
	return mainClass;
}

Arguements GameJson::getGameArguements() const
{
	return gameArguements;
}

QString GameJson::getAssetsIndex() const
{
	if(inheritsFromJson)
		return inheritsFromJson->getAssetsIndex();
	else
		return assetsIndex;
}
