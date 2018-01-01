#include "Path.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QStandardPaths>
#include <QSettings>
#include <QDebug>

QString Path::JavaPath()
{
	QFileInfo path(QSettings().value("javaPath").toString());
	if(!path.exists()){
		throw QString("Java not exist.");
	}
	return path.filePath();
}

QString Path::launcherPath()
{
	return QCoreApplication::applicationDirPath();
}

QString Path::corePath()
{
	return QSettings().value("path/corePath", QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/.minecraft").toString();
}

QString Path::libsPath()
{
	auto path = QSettings().value("path/libsPath", corePath() + "/libraries").toString();
	replaceCore(path);
	return path;
}

QString Path::nativesPath()
{
	auto path = QSettings().value("path/nativesPath", corePath() + "/natives").toString();
	replaceCore(path);
	return path;
}

QString Path::versionsPath()
{
	auto path = QSettings().value("path/versionsPath", corePath() + "/versions").toString();
	replaceCore(path);
	return path;
}

QString Path::assetsPath()
{
	auto path = QSettings().value("path/assetsPath", corePath() + "/assets").toString();
	replaceCore(path);
	return path;
}

QString Path::indexesPath()
{
	auto path = QSettings().value("path/indexesPath", assetsPath() + "/indexes").toString();
	replaceAll(path);
	return path;
}

QString Path::objectsPath()
{
	auto path = QSettings().value("path/objectsPath", assetsPath() + "/objects").toString();
	replaceAll(path);
	return path;
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
