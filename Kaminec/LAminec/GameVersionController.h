#ifndef GAMEVERSIONCONTROLLER_H
#define GAMEVERSIONCONTROLLER_H

#include "messenger/GameVersion.h"

#include <QList>

class GameVersionController
{
public:
	GameVersionController();
	QList<GameVersion> getGameVersions() const;

private:
	QList<GameVersion> gameVersions_;
};

#endif // GAMEVERSIONCONTROLLER_H
