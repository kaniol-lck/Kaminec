#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include "messager/fileitem.h"

#include <QObject>
#include <QList>
#include <QJsonObject>

class AssetsManager : public QObject
{
	Q_OBJECT
public:
	explicit AssetsManager(QObject *parent, QString assetsIndex);

	QList<FileItem> getDownloadAssetsUrls();

signals:

public slots:

private:
	static QString resourcesDownload_;
	QJsonObject assets_;
	QString corePath_;
};

#endif // ASSETSMANAGER_H
