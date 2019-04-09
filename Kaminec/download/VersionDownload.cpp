#include "VersionDownload.h"

#include "GameJsonDownload.h"
#include "GameClientDownload.h"
#include "GameLibrariesDownload.h"
#include "AssetIndexDownload.h"
#include "AssetObjectsDownload.h"

#include <cassert>

VersionDownload::VersionDownload(QObject *parent, const GameVersion &version) :
	QObject(parent),
	version_(version),
	gameJsonDownload_(new GameJsonDownload(this, version))
{
	if(gameJsonDownload_->exists())
		loadJson();
	if(assetIndexDownload_ && assetIndexDownload_->exists())
		loadAssetIndex();
}

GameJsonDownload *VersionDownload::gameJsonDownload()
{
	return gameJsonDownload_;
}

GameClientDownload *VersionDownload::gameClientDownload()
{
	assert(gameClientDownload_);
	return gameClientDownload_;
}

GameLibrariesDownload *VersionDownload::gameLibrariesDownload()
{
	assert(gameLibrariesDownload_);
	return gameLibrariesDownload_;
}

AssetObjectsDownload *VersionDownload::assetObjectsDownload()
{
	assert(assetObjectsDownload_);
	return assetObjectsDownload_;
}

AssetIndexDownload *VersionDownload::assetIndexDownload()
{
	assert(assetIndexDownload_);
	return assetIndexDownload_;
}

void VersionDownload::loadJson()
{
	jsonKit_ = std::make_shared<JsonKit>(version_.versionName());
	gameClientDownload_ = new GameClientDownload(this, jsonKit_->client());
	gameLibrariesDownload_ = new GameLibrariesDownload(this, jsonKit_->libraries());
	assetIndexDownload_ = new AssetIndexDownload(this, jsonKit_->assetIndex());
	if(assetIndexDownload_->exists())
		loadAssetIndex();
}

void VersionDownload::loadAssetIndex()
{
	assetKit_ = std::make_shared<AssetKit>(jsonKit_->assetIndex().id());
	assetObjectsDownload_ = new AssetObjectsDownload(this, assetKit_->assetObjects());
}
