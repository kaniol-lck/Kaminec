#ifndef VERSIONMANIFESTDOWNLOAD_H
#define VERSIONMANIFESTDOWNLOAD_H

#include <QObject>

class VersionManifestDownload : public QObject
{
	Q_OBJECT
public:
	explicit VersionManifestDownload(QObject *parent, QString fileName);

	bool exists();
	void AddDownload();

	QVariant waitForDownloaded();

signals:
	void downloadFinished();

private:
	QString fileName_;
};

#endif // VERSIONMANIFESTDOWNLOAD_H
