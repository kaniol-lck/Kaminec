#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include "fileitem.h"
#include "downloadmanager.h"

#include <QJsonDocument>
#include <QVariantMap>
#include <QStringList>
#include <QPair>
#include <QUrl>

class JsonManager
{
public:
    JsonManager(QString gamePath, QString version);

    QStringList                   getLibfileList();
    QStringList                   getExtractfileList();
    QList<FileItem>               getDownloadLibUrls();
    QList<FileItem>               getDownloadAssertUrls();
    QStringList                   getMCArgs();
    QStringList                   getMCMainClass();
    QString                       getAssetIndex();
    QUrl                          getDownloadClientUrl();

private:
    QJsonDocument jsonDoc;
    QVariantMap jsonMap;
    QList<QVariant> libList;
    DownloadManager jsonDownload;
    QString gameDir;
};

#endif // JSONMANAGER_H
