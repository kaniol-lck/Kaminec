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

QString Path::corePath()
{
	return Custom().getCoreGameFileDirectory();
}

QString Path::libsPath()
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

QString Path::indexesPath()
{
	auto path = Custom().getAssetsIndexesDirectory();
	replaceAll(path);
	return path;
}

QString Path::objectsPath()
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
			.arg(indexesPath(), index);
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
