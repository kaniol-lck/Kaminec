#ifndef GAMEJSONDOWNLOAD_H
#define GAMEJSONDOWNLOAD_H

#include "FileDownload.h"
#include "messenger/GameVersion.h"

#include <QUrl>

class GameJsonDownload : public FileDownload
{
	Q_OBJECT
public:
	explicit GameJsonDownload(QObject *parent, const GameVersion &version);

	bool exists() const;
	void addDownload();

private:
	GameVersion version_;
};

#endif // GAMEJSONDOWNLOAD_H
