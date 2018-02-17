#ifndef LAUNCHJSON_H
#define LAUNCHJSON_H

#include "core/json/main/JsonKit.h"

#include <memory>

class LaunchJson
{
public:
	LaunchJson(QString version);

	QString getGameJarPath() const;

	QStringList getLibraryPaths() const;

	QStringList getExtractPaths() const;

	QString getMainClass() const;

	Arguments getGameArguments() const;

	QString getAssetsIndexId() const;

private:
	JsonKit jsonKit_;

};

#endif // LAUNCHJSON_H
