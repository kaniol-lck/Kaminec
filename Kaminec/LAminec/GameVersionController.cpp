#include "GameVersionController.h"

#include "assistance/Path.h"

#include <QDir>

GameVersionController::GameVersionController()
{
	QDir versionsDir(Path::versionsPath());
	for(const auto &versionName : versionsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System))
		gameVersions_ << GameVersion(versionName);
}

QList<GameVersion> GameVersionController::getGameVersions() const
{
	return gameVersions_;
}
