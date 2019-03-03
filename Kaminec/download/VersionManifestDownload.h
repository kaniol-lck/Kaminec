#ifndef VERSIONMANIFESTDOWNLOAD_H
#define VERSIONMANIFESTDOWNLOAD_H

#include <QObject>

class VersionManifestDownload : public QObject
{
	Q_OBJECT
public:
	explicit VersionManifestDownload(QObject *parent = nullptr);

	void AddDownload();

	QVariant waitForDownloaded();

signals:
	void downloadFinished();

public slots:
};

#endif // VERSIONMANIFESTDOWNLOAD_H
