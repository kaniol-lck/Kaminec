#include "jsonmanager.h"

#include <QFile>
#include <QByteArray>
#include <algorithm>
#include <QDebug>


jsonManager::jsonManager(QString jsonName)
{
    QFile jsonFile(jsonName);

    if(!jsonFile.exists())qDebug()<<"jsonfile file does not exist";
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))qDebug()<<"Open failed";
    qDebug()<<"jsonfile file opened";

    QByteArray jsonByte;
    jsonByte.resize(jsonFile.bytesAvailable());
    jsonByte = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError ok;
    jsonDoc = QJsonDocument::fromJson(jsonByte,&ok);
    if(ok.error != QJsonParseError::NoError){qDebug()<<"Json failed."<<endl<<ok.error;}

    jsonMap = jsonDoc.toVariant().toMap();
    libList = jsonMap.take("libraries").toList();
}



QStringList jsonManager::getLibfileList()
{
    return std::accumulate(libList.begin(),libList.end(),QStringList(),
                           [](QStringList libfileList,QVariant libElem){
        return libElem
                .toMap().take("downloads")
                .toMap().contains("artifact")?
                    (libfileList<<libElem
                            .toMap().take("downloads")
                            .toMap().take("artifact")
                            .toMap().take("path")
                            .toString()):
                    libfileList;
    });
}



QStringList jsonManager::getExtractfileList()
{
    return std::accumulate(libList.begin(),libList.end(),QStringList(),
                           [](QStringList libfileList,QVariant libElem){
        return libElem.toMap().contains("extract")?
                    (libfileList<<libElem
                            .toMap().take("downloads")
                            .toMap().take("classifiers")
                            .toMap().take("natives-windows")
                            .toMap().take("path")
                            .toString()):
                    libfileList;
    });
}


#include <QPair>

QList<QPair<QString, QString> > jsonManager::getDownloadfileUrls()
{
    return std::accumulate(libList.begin(),libList.end(),QList<QPair<QString, QString>>(),
                           [](QList<QPair<QString,QString>> libUrls,QVariant libElem){
        return libElem
                .toMap().take("downloads")
                .toMap().contains("artifact")?
                    libUrls<<qMakePair(libElem
                              .toMap().take("downloads")
                              .toMap().take("artifact")
                              .toMap().take("url")
                              .toString(),
                                       libElem
                              .toMap().take("downloads")
                              .toMap().take("artifact")
                              .toMap().take("path")
                              .toString()):

                    libUrls<<qMakePair(libElem
                              .toMap().take("downloads")
                              .toMap().take("classifiers")
                              .toMap().take("natives-windows")
                              .toMap().take("url")
                              .toString(),
                                       libElem
                              .toMap().take("downloads")
                              .toMap().take("classifiers")
                              .toMap().take("natives-windows")
                              .toMap().take("path")
                              .toString());
    });
}



QString jsonManager::getMCArgs()
{
    return jsonMap.take("minecraftArguments").toString();
}



QString jsonManager::getMCMainClass()
{
    return jsonMap.take("mainClass").toString();
}

QString jsonManager::getAssetIndex()
{
    return jsonMap.take("assets")
            .toString();
}
