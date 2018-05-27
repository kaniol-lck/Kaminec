#ifndef PATH_H
#define PATH_H

#include <QString>

class Path {
public:
	//game
	static QString JavaPath();
	static QString launcherPath();
	static QString logsPath();
	static QString corePath();
	static QString librariesPath();
	static QString nativesPath();
	static QString versionsPath();
	static QString assetsPath();
	static QString assetIndexesPath();
	static QString assetObjectsPath();

	//launcher
	static QString loggerPath();

	static QString getJsonPath(const QString &version);
	static QString getAssetIndexPath(const QString &index);

private:
	static void replaceLauncher(QString &path);
	static void replaceCore(QString &path);
	static void replaceAll(QString &path);
};

#endif // PATH_H
