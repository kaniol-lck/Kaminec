#include "LaunchJson.h"

LaunchJson::LaunchJson(QString version) :
	jsonKit(version)
{

}

QString LaunchJson::getGameJarPath() const
{
	return QString("/%1/%1.jar").arg(jsonKit.jarName());
}

QStringList LaunchJson::getLibraryPaths() const
{
	QStringList librariesPaths;

	for(const auto& library : jsonKit.libraries()){
		if(library.isNatives()) continue;//ignore extract file
		librariesPaths << library.path();
	}
	return librariesPaths;
}

QStringList LaunchJson::getExtractPaths() const
{
	QStringList librariesPaths;
	for(const auto& library : jsonKit.libraries()){
		if(library.isNatives())
			librariesPaths << library.path();//keep extract file only
	}

	return librariesPaths;
}

QString LaunchJson::getMainClass() const
{
	return jsonKit.mainClass();
}

Arguments LaunchJson::getGameArguments() const
{
	return jsonKit.minecraftArguments();
}

QString LaunchJson::getAssetsIndexId() const
{
	return jsonKit.assetIndex().id();
}
