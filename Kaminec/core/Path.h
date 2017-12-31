#ifndef PATH_H
#define PATH_H

#include <QString>
#include <QSettings>

class Path {
public:
	Path() = delete;

	static QString JavaPath();
	static QString launcherPath();
	static QString corePath();
	static QString libsPath();
	static QString versionsPath();
	static QString assetsPath();
	static QString indexesPath();
	static QString objectsPath();

private:
	static void replaceLauncher(QString& path);
	static void replaceCore(QString& path);
	static void replaceAll(QString& path);
	static QSettings settings;
};

#endif // PATH_H
