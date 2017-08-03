#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include "fileitem.h"
#include "downloadmanager.h"
#include "downloadmanagerplus.h"

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

    QStringList                   getLibfileList();
    QStringList                   getExtractfileList();
    QList<FileItem>               getDownloadLibUrls();
    QList<FileItem>               getDownloadAssertUrls();
    QStringList                   getMCArgs();
    QStringList                   getMCMainClass();
    QString                       getAssetIndex();
	FileItem getDownloadClientUrl();

private:
    QJsonDocument jsonDoc;
    QVariantMap jsonMap;
    QList<QVariant> libList;
    DownloadManagerPlus *jsonDownload;
	QString corePath;
};

#endif // JSONMANAGER_H
