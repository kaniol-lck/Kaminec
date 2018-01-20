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
	FileItem		getDownloadAssetsFileUrl();
	QStringList     getGameArgs();
	QStringList     getGameMainClass();
	QStringList     getJVMArgs();
	QString         getAssetsIndex();
	FileItem        getDownloadClientUrl();
	QStringList     getVersionChain();

private:
	QJsonDocument jsonDoc_;
	QVariant jsonContent_;
	QList<QVariant> libList_;
	DownloadManagerPlus *jsonDownload_;
	QString corePath_;
};

#endif // JSONMANAGER_H
