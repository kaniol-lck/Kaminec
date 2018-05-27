#include "Path.h"

#include "assistance/Custom.h"

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
	return launcherPath() + "/logs";
}

QString Path::corePath()
{
	return Custom().getCoreGameFileDirectory();
}

QString Path::librariesPath()
{
	auto path = Custom().getGameLibrariesDirectory();
	replaceCore(path);
	return path;
}

QString Path::nativesPath()
{
	auto path = Custom().getGameNativesDirectory();
	replaceCore(path);
	return path;
}

QString Path::versionsPath()
{
	auto path = Custom().getGameVersionsDirectory();
	replaceCore(path);
	return path;
}

QString Path::assetsPath()
{
	auto path = Custom().getAssetsDirectory();
	replaceCore(path);
	return path;
}

QString Path::assetIndexesPath()
{
	auto path = Custom().getAssetsIndexesDirectory();
	replaceAll(path);
	return path;
}

QString Path::assetObjectsPath()
{
	auto path = Custom().getAssetsObjectsDirectory();
	replaceAll(path);
	return path;
}

QString Path::loggerPath()
{
	auto path = Custom().getLoggerDirectory();
	replaceAll(path);
	return path;
}

QString Path::getJsonPath(const QString& version)
{
	return QString("%1/%2/%2.json")
			.arg(versionsPath(), version);
}

QString Path::getAssetIndexPath(const QString &index)
{
	return QString("%1/2%.json")
			.arg(assetIndexesPath(), index);
}

void Path::replaceLauncher(QString &path)
{
	path.replace("<launcher>", launcherPath());
	return;
}

void Path::replaceCore(QString &path)
{
	replaceLauncher(path);
	path.replace("<core>", corePath());
	return;
}

void Path::replaceAll(QString &path)
{
	replaceCore(path);
	path.replace("<assets>", assetsPath());
	return;
}
