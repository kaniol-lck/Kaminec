#include "Path.h"

#include "assistance/Custom.h"
#include "assistance/PathReplacer.h"

#include <QCoreApplication>

QString Path::JavaPath()
{
	return Custom().getJavaDirectory();
}

QString Path::launcherPath()
{
	return QCoreApplication::applicationDirPath();
}

QString Path::logsPath()
{
	return PathReplacer::replace(Custom().getLoggerDirectory());
}

QString Path::corePath()
{
	return Custom().getCoreGameFileDirectory();
}

QString Path::librariesPath()
{
	auto path = PathReplacer::replace(Custom().getGameLibrariesDirectory());
	return path;
}

QString Path::nativesPath()
{
	auto path = PathReplacer::replace(Custom().getGameNativesDirectory());
	return path;
}

QString Path::versionsPath()
{
	auto path = PathReplacer::replace(Custom().getGameVersionsDirectory());
	return path;
}

QString Path::assetsPath()
{
	auto path = PathReplacer::replace(Custom().getAssetsDirectory());
	return path;
}

QString Path::assetIndexesPath()
{
	auto path = PathReplacer::replace(Custom().getAssetsIndexesDirectory());
	return path;
}

QString Path::assetObjectsPath()
{
	auto path = PathReplacer::replace(Custom().getAssetsObjectsDirectory());
	return path;
}

QString Path::loggerPath()
{
	auto path = PathReplacer::replace(Custom().getLoggerDirectory());
	return path;
}

QString Path::jsonPath(const QString& version)
{
	return PathReplacer::replace("<versions>/%1/%1.json").arg(version);
}

QString Path::assetIndexPath(const QString &index)
{
	return PathReplacer::replace("<indexes>/%1.json").arg(index);
}
