#include "PathReplacer.h"

#include "assistance/Custom.h"

#include <QCoreApplication>

QString PathReplacer::replace(QString &path)
{
	Custom custom;
	path.replace("<libraries>", custom.getGameLibrariesDirectory());
	path.replace("<indexes>", custom.getAssetsIndexesDirectory());
	path.replace("<objects>", custom.getAssetsObjectsDirectory());
	path.replace("<assets>", custom.getAssetsDirectory());
	path.replace("<versions>", custom.getGameVersionsDirectory());
	path.replace("<core>", custom.getCoreGameFileDirectory());
	path.replace("<launcher>", QCoreApplication::applicationDirPath());
	return path;
}

QString PathReplacer::replace(const QString &path){
	QString p(path);
	return replace(p);
}
