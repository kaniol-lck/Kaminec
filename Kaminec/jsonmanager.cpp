#include "jsonmanager.h"

#include <QPair>
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <algorithm>
#include <QDebug>


jsonManager::jsonManager(QString gamePath,QString version):
    gameDir(gamePath)
{
    QFile jsonFile(gamePath+QString("/versions/%1/%1.json").arg(version));

    if(!jsonFile.exists())qDebug()<<"jsonfile file does not exist";
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Open failed";
        QMessageBox::about(0,"Not find json file","Json file NOT find,The program will terminate.");
    }
    qDebug()<<"jsonfile("<<version<<".json) file opened";

    QByteArray jsonByte;
    jsonByte.resize(jsonFile.bytesAvailable());
    jsonByte = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError ok;
    jsonDoc = QJsonDocument::fromJson(jsonByte,&ok);
    if(ok.error != QJsonParseError::NoError){qDebug()<<"Json failed."<<endl<<ok.error;}

    jsonMap = jsonDoc.toVariant().toMap();
    libList = jsonMap.value("libraries").toList();
}



QStringList jsonManager::getLibfileList()
{
    return std::accumulate(libList.begin(),libList.end(),QStringList(),
                           [](QStringList libfileList,QVariant libElem){
        return libElem
                .toMap().value("downloads")
                .toMap().contains("artifact")?
                    (libfileList<<libElem
                            .toMap().value("downloads")
                            .toMap().value("artifact")
                            .toMap().value("path")
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
                            .toMap().value("downloads")
                            .toMap().value("classifiers")
                            .toMap().value("natives-windows")
                            .toMap().value("path")
                            .toString()):
                    libfileList;
    });
}



QList<QPair<QUrl, QString> > jsonManager::getDownloadLibUrls()
{
    return std::accumulate(libList.begin(),libList.end(),QList<QPair<QUrl, QString>>(),
                           [](QList<QPair<QUrl,QString>> libUrls,QVariant libElem){
        return libElem
                .toMap().value("downloads")
                .toMap().contains("classifiers")?
                    libUrls<<qMakePair(libElem
                              .toMap().value("downloads")
                              .toMap().value("classifiers")
                              .toMap().value("natives-windows")
                              .toMap().value("url")
                              .toUrl(),
                                       libElem
                              .toMap().value("downloads")
                              .toMap().value("classifiers")
                              .toMap().value("natives-windows")
                              .toMap().value("path")
                              .toString()):
                    libUrls<<qMakePair(libElem
                              .toMap().value("downloads")
                              .toMap().value("artifact")
                              .toMap().value("url")
                              .toUrl(),
                                       libElem
                              .toMap().value("downloads")
                              .toMap().value("artifact")
                              .toMap().value("path")
                              .toString());
    });
}

#include "downloadmanager.h"

QList<QPair<QUrl, QString> > jsonManager::getDownloadAssertUrls()
{
    QUrl assertUrl=jsonMap.value("assetIndex")
                      .toMap().value("url").toUrl();

    jsonDownload.append(qMakePair(assertUrl,gameDir+"/assets/indexes/1.10.json"));
    jsonDownload.waitForFinished();
    //try{
    QFile f(gameDir+"/assets/indexes/1.10.json");//!

    QByteArray assertByte;

    if(!f.exists())qDebug()<<"jsonfile(1.10.json) file does not exist";
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))qDebug()<<"Open failed";
    qDebug()<<"jsonfile(1.10.json) file opened!!!";
    assertByte.resize(f.bytesAvailable());
    assertByte = f.readAll();
    f.close();

    QJsonParseError ok;
    auto assertDoc = QJsonDocument::fromJson(assertByte,&ok);
    if(ok.error != QJsonParseError::NoError){qDebug()<<"Json failed."<<endl<<ok.error;}

    auto objectMap = assertDoc.toVariant().toMap().value("objects").toMap();

    QList<QPair<QUrl, QString>> downloadAssertUrls;

    for(auto it:objectMap){
        QString hash = it.toMap().value("hash").toString();
        QString name = QString("%1/%2").arg(hash.left(2),hash);
        QUrl url = "http://resources.download.minecraft.net/"+name;
        downloadAssertUrls<<qMakePair(url,name);
    }

    qDebug()<<"ha?";
    //这个地方不知道为什么“downloadAssertUrls”放循环里正常，外边访问就不对
    for(auto& i:downloadAssertUrls)
        qDebug()<<i;
    return downloadAssertUrls;
    //}catch(...){
    //        qDebug()<<"exception";
    //        throw;
    //}
}



QStringList jsonManager::getMCArgs()
{
    return jsonMap.value("minecraftArguments").toString().split(" ");
}



QStringList jsonManager::getMCMainClass()
{
    return jsonMap.value("mainClass").toStringList();
}

QString jsonManager::getAssetIndex()
{
    return jsonMap.value("assets")
            .toString();
}

QUrl jsonManager::getDownloadClientUrl()
{
    return jsonMap.value("downloads").toMap()
                  .value("client").toMap()
                  .value("url").toString();
}
