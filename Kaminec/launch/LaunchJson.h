#ifndef LAUNCHJSON_H
#define LAUNCHJSON_H

#include "kits/JsonKit/JsonKit.h"

#include <memory>

class LaunchJson
{
public:
	LaunchJson(const QString &version);

	QString getGameJarPath() const;

	QStringList getLibraryPaths() const;

	QStringList getNativesPaths() const;

	QString getMainClass() const;

	Arguments getGameArguments() const;

	QString getAssetsIndexId() const;

private:
	JsonKit jsonKit_;

};

#endif // LAUNCHJSON_H
