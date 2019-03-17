#ifndef VERSIONDOWNLOAD_H
#define VERSIONDOWNLOAD_H

#include "kits/JsonKit/JsonKit.h"
#include "kits/AssetKit/AssetKit.h"
#include "messenger/GameVersion.h"

#include <QObject>
#include <memory>

class JsonKit;
class GameJsonDownload;
class GameClientDownload;
class GameLibrariesDownload;
class AssetIndexDownload;
class AssetObjectsDownload;

class VersionDownload : public QObject
{
	Q_OBJECT
public:
	explicit VersionDownload(QObject *parent, const GameVersion &version);

	GameJsonDownload *gameJsonDownload();
	AssetIndexDownload *assetIndexDownload();
	GameClientDownload *gameClientDownload();
	GameLibrariesDownload *gameLibrariesDownload();
	AssetObjectsDownload *assetObjectsDownload();

public slots:
	void loadJson();
	void loadAssetIndex();

private:
	GameVersion version_;
	std::shared_ptr<JsonKit> jsonKit_;
	std::shared_ptr<AssetKit> assetKit_;
	GameJsonDownload *gameJsonDownload_;
	AssetIndexDownload *assetIndexDownload_ = nullptr;

	GameClientDownload *gameClientDownload_ = nullptr;
	GameLibrariesDownload *gameLibrariesDownload_ = nullptr;
	AssetObjectsDownload *assetObjectsDownload_ = nullptr;

};

#endif // VERSIONDOWNLOAD_H
