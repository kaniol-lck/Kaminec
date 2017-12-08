#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include "messager/fileitem.h"
#include "downloader/downloadmanagerplus.h"

#include <QJsonDocument>
#include <QVariantMap>
#include <QStringList>
#include <QObject>
#include <QPair>
#include <QUrl>

class JsonManager : public QObject
{
    Q_OBJECT
public:
	JsonManager(QObject *parent, QString version);

	QStringList     getLibfileList();
	QStringList     getExtractfileList();
	QList<FileItem> getDownloadLibUrls();
	FileItem		getDownloadAssetFileUrl();
	QStringList     getGameArgs();
	QStringList     getGameMainClass();
	QStringList     getJVMArgs();
	QString         getAssetIndex();
	FileItem        getDownloadClientUrl();
	QStringList     getVersionChain();

private:
    QJsonDocument jsonDoc;
	QVariant jsonContent;
    QList<QVariant> libList;
    DownloadManagerPlus *jsonDownload;
	QString corePath;
};

#endif // JSONMANAGER_H
