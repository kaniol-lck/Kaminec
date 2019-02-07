#include "GameVersionController.h"

#include "assistance/Path.h"

#include <QDir>

GameVersionController::GameVersionController()
{}

QList<GameVersion> GameVersionController::getAllVersions()
{
	QList<GameVersion> versions;
	QDir versionsDir(Path::versionsPath());
	for(auto versionName : versionsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System)){
		versions << GameVersion(versionName);
	}
	return versions;
}
