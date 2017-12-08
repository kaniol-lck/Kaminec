#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "fileitem.h"

#include <QObject>
#include <QList>
#include <QJsonObject>

class AssetManager : public QObject
{
	Q_OBJECT
public:
	explicit AssetManager(QObject *parent, QString assertIndex);

	QList<FileItem> getDownloadAssetUrls();

signals:

public slots:

private:
	QJsonObject asset;
	QString corePath;
};

#endif // ASSETMANAGER_H
