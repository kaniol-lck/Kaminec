#ifndef GAMEVERSIONCONTROLLER_H
#define GAMEVERSIONCONTROLLER_H

#include "messenger/GameVersion.h"

class GameVersionController
{
public:
	GameVersionController();
	QList<GameVersion> getAllVersions();
};

#endif // GAMEVERSIONCONTROLLER_H
