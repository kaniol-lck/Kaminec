#ifndef PATH_H
#define PATH_H

#include <QString>

class Path {
public:

	static QString JavaPath();
	static QString launcherPath();
	static QString corePath();
	static QString libsPath();
	static QString nativesPath();
	static QString versionsPath();
	static QString assetsPath();
	static QString indexesPath();
	static QString objectsPath();

	static QString getJsonPath(const QString &version);
	static QString getAssetIndexPath(const QString &index);

private:
	static void replaceLauncher(QString &path);
	static void replaceCore(QString &path);
	static void replaceAll(QString &path);
};

#endif // PATH_H
