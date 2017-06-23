#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QJsonDocument>
#include <QVariantMap>
#include <QStringList>
#include <QPair>
#include <QUrl>

class jsonManager
{
public:
    jsonManager(QString jsonName);

    QStringList                   getLibfileList();
    QStringList                   getExtractfileList();
    QList<QPair<QUrl,QString>>    getDownloadLibUrls();
    QList<QPair<QUrl,QString>>    getDownloadAssertUrls();
    QStringList                   getMCArgs();
    QStringList                   getMCMainClass();
    QString                       getAssetIndex();

private:
    QJsonDocument jsonDoc;
    QVariantMap jsonMap;
    QList<QVariant> libList;
};

#endif // JSONMANAGER_H
