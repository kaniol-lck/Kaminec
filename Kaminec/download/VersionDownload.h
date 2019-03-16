#ifndef VERSIONDOWNLOAD_H
#define VERSIONDOWNLOAD_H

#include "kits/JsonKit/JsonKit.h"
#include "messenger/GameVersion.h"

#include <QObject>
#include <memory>

class JsonKit;
class GameJsonDownload;
class GameClientDownload;
class GameLibrariesDownload;

class VersionDownload : public QObject
{
	Q_OBJECT
public:
	explicit VersionDownload(QObject *parent, const GameVersion &version);

	GameJsonDownload *gameJsonDownload();
	GameClientDownload *gameClientDownload();
	GameLibrariesDownload *gameLibrariesDownload();

public slots:
	void loadJson();

private:
	GameVersion version_;
	std::shared_ptr<JsonKit> jsonKit_;
	GameJsonDownload *gameJsonDownload_;

	GameClientDownload *gameClientDownload_ = nullptr;
	GameLibrariesDownload *gameLibrariesDownload_ = nullptr;

};

#endif // VERSIONDOWNLOAD_H
