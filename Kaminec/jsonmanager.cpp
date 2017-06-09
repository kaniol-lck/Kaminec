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


#include <QPair>

QList<QPair<QUrl, QString> > jsonManager::getDownloadLibUrls()
{
    return std::accumulate(libList.begin(),libList.end(),QList<QPair<QUrl, QString>>(),
                           [](QList<QPair<QUrl,QString>> libUrls,QVariant libElem){
        return libElem
                .toMap().value("downloads")
                .toMap().contains("artifact")?
                    libUrls<<qMakePair(libElem
                              .toMap().value("downloads")
                              .toMap().value("artifact")
                              .toMap().value("url")
                              .toUrl(),
                                       libElem
                              .toMap().value("downloads")
                              .toMap().value("artifact")
                              .toMap().value("path")
                              .toString()):

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
                              .toString());
    });
}


#include <QByteArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

QList<QPair<QUrl, QString> > jsonManager::getDownloadAssertUrls()
{
    //QUrl assertUrl=jsonMap.value("assetIndex")
    //                  .toMap().value("url").toUrl();
    //
    //qDebug()<<"start download:"<<assertUrl;
    //QNetworkAccessManager m_qnam;
    //QNetworkRequest qnr(assertUrl);
    //QNetworkReply* reply = m_qnam.get(qnr); //m_qnam是QNetworkAccessManager对象
    //
    //QEventLoop eventLoop;
    //QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    //eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    //
    //qDebug()<<"finished:"<<reply->readAll()<<"???";

    QByteArray assertByte;




    QFile f("J:/库/桌面/1.10.json");

    if(!f.exists())qDebug()<<"jsonfile file does not exist";
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))qDebug()<<"Open failed";
    qDebug()<<"jsonfile file opened!!!";
    assertByte.resize(f.bytesAvailable());
    assertByte = f.readAll();
    f.close();



    QJsonParseError ok;
    auto assertDoc = QJsonDocument::fromJson(assertByte,&ok);
    if(ok.error != QJsonParseError::NoError){qDebug()<<"Json failed."<<endl<<ok.error;}

    auto objectMap = assertDoc.toVariant().toMap().value("objects").toMap();

    QList<QPair<QUrl, QString>> downloadAssertUrls;

    for(auto it=objectMap.begin();it!=objectMap.end();it++){
        QString hash = it.value().toMap().value("hash").toString();
        QString name = it.key();
        QUrl url = QString("resources.download.minecraft.net/%1/%2").arg(hash.left(2),hash);
        downloadAssertUrls.push_back(qMakePair(url,name));
    }

    //这个地方不知道为什么“downloadAssertUrls”放循环里正常，外边访问就不对
    qDebug()<<downloadAssertUrls;
    return downloadAssertUrls;
}



QString jsonManager::getMCArgs()
{
    return jsonMap.value("minecraftArguments").toString();
}



QString jsonManager::getMCMainClass()
{
    return jsonMap.value("mainClass").toString();
}

QString jsonManager::getAssetIndex()
{
    return jsonMap.value("assets")
            .toString();
}
