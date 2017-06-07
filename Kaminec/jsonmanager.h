#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QJsonDocument>
#include <QVariantMap>
#include <QStringList>
#include <QPair>

class jsonManager
{
public:
    jsonManager(QString jsonName);

    QStringList                   getLibfileList();
    QStringList                   getExtractfileList();
    QList<QPair<QString,QString>> getDownloadfileUrls();
    QString                       getMCArgs();
    QString                       getMCMainClass();
    QString                       getAssetIndex();

private:
    QJsonDocument jsonDoc;
    QVariantMap jsonMap;
    QList<QVariant> libList;
};

#endif // JSONMANAGER_H
