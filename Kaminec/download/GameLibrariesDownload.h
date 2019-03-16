#ifndef GAMELIBRARIESDOWNLOAD_H
#define GAMELIBRARIESDOWNLOAD_H

#include "FileDownload.h"
#include "kits/JsonKit/Library.h"
#include "messenger/DownloadInfo.h"

class GameLibrariesDownload : public FileDownload
{
public:
	explicit GameLibrariesDownload(QObject *parent, const QList<Library> &libraries);

	bool exists() const;
	void addDownload();

private:
	QList<Library> libraries_;
	QList<DownloadInfo> libraryInfos_;
};

#endif // GAMELIBRARIESDOWNLOAD_H
