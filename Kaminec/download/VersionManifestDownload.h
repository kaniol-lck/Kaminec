#ifndef VERSIONMANIFESTDOWNLOAD_H
#define VERSIONMANIFESTDOWNLOAD_H

#include "FileDownload.h"

class VersionManifestDownload : public FileDownload
{
	Q_OBJECT
public:
	explicit VersionManifestDownload(QObject *parent, QString fileName);

	bool exists() const;
	void addDownload();

	QVariant waitForDownloaded();

private:
	QString fileName_;
};

#endif // VERSIONMANIFESTDOWNLOAD_H
