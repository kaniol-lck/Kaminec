#ifndef GAMECLIENTDOWNLOAD_H
#define GAMECLIENTDOWNLOAD_H

#include "FileDownload.h"
#include "kits/JsonKit/GameCoreJar.h"

class GameClientDownload : public FileDownload
{
	Q_OBJECT
public:
	explicit GameClientDownload(QObject *parent, const GameCoreJar &client);

	bool exists() const;
	void addDownload();

private:
	GameCoreJar client_;
};

#endif // GAMECLIENTDOWNLOAD_H
