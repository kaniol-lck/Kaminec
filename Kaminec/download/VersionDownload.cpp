#include "VersionDownload.h"

#include "GameJsonDownload.h"
#include "GameClientDownload.h"
#include "GameLibrariesDownload.h"

#include <cassert>

VersionDownload::VersionDownload(QObject *parent, const GameVersion &version) :
	QObject(parent),
	version_(version),
	gameJsonDownload_(new GameJsonDownload(this, version))
{
	if(gameJsonDownload_->exists())
		loadJson();
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

void VersionDownload::loadJson()
{
	jsonKit_ = std::make_shared<JsonKit>(version_.versionName());
	gameClientDownload_ = new GameClientDownload(this, jsonKit_->client());
	gameLibrariesDownload_ = new GameLibrariesDownload(this, jsonKit_->libraries());
}
