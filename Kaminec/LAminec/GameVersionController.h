#ifndef GAMEVERSIONCONTROLLER_H
#define GAMEVERSIONCONTROLLER_H

#include "messenger/GameVersion.h"

class GameVersionController
{
public:
	GameVersionController();
	QList<GameVersion> getGameVersions() const;

private:
	QList<GameVersion> gameVersions_;
};

#endif // GAMEVERSIONCONTROLLER_H
