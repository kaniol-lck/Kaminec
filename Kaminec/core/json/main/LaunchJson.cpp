#include "LaunchJson.h"

LaunchJson::LaunchJson(QString version) :
	jsonKit_(version)
{

}

QString LaunchJson::getGameJarPath() const
{
	return QString("/%1/%1.jar").arg(jsonKit_.jarName());
}

QStringList LaunchJson::getLibraryPaths() const
{
	QStringList libraryPaths;

	for(const auto& library : jsonKit_.libraries()){
		if(library.isNatives()) continue;//ignore extract file
		libraryPaths << library.path();
	}
	return libraryPaths;
}

QStringList LaunchJson::getExtractPaths() const
{
	QStringList extractPaths;
	for(const auto& library : jsonKit_.libraries()){
		if(library.isNatives())
			extractPaths << library.path();//keep extract file only
	}

	return extractPaths;
}

QString LaunchJson::getMainClass() const
{
	return jsonKit_.mainClass();
}

Arguments LaunchJson::getGameArguments() const
{
	return jsonKit_.minecraftArguments();
}

QString LaunchJson::getAssetsIndexId() const
{
	return jsonKit_.assetIndex().id();
}
