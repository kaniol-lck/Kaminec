#include "JsonManager.h"
#include "fileitem.h"

#include <QPair>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QStandardPaths>
#include <QByteArray>
#include <algorithm>
#include <QDebug>


JsonManager::JsonManager(QObject *parent, QString version):
    QObject(parent),
	jsonDownload(new DownloadManagerPlus(this)),
	corePath(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).toString())
{
	QFile jsonFile(corePath+QString("/versions/%1/%1.json").arg(version));

    if(!jsonFile.exists())qDebug()<<"jsonfile file does not exist";
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug()<<"Open failed:"<<corePath+QString("/versions/%1/%1.json").arg(version);
        QMessageBox::about(0,"Not find json file","Json file NOT find,The program will terminate.");
    }
    qDebug()<<"jsonfile("<<version<<".json) file opened:"<<jsonFile.fileName();

    QByteArray jsonByte;
	qDebug()<<QString(jsonByte);
    jsonByte.resize(jsonFile.bytesAvailable());
    jsonByte = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError ok;
    jsonDoc = QJsonDocument::fromJson(jsonByte,&ok);
    if(ok.error != QJsonParseError::NoError){qDebug()<<"Json failed."<<endl<<ok.error;}

    jsonMap = jsonDoc.toVariant().toMap();
    libList = jsonMap.value("libraries").toList();
}



QStringList JsonManager::getLibfileList()
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



QStringList JsonManager::getExtractfileList()
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



QList<FileItem> JsonManager::getDownloadLibUrls()
{
    return std::accumulate(libList.begin(),libList.end(),QList<FileItem>(),
                           [](QList<FileItem> libUrls,QVariant libElem){
		return (libElem.toMap().value("downloads").toMap().contains("classifiers") &&
				!libElem.toMap().value("downloads").toMap().value("classifiers").toMap().contains("test") &&
				libElem.toMap().contains("natives") &&
				libElem.toMap().value("natives").toMap().contains("windows") &&
				libElem.toMap().value("downloads").toMap().value("classifiers").toMap().contains(
					libElem.toMap().value("natives").toMap().value("windows").toString()))?
					libUrls<<FileItem(libElem.toMap().value("name").toString(),
									  libElem.toMap().value("downloads").toMap().value("classifiers").toMap().value(
										  libElem.toMap().value("natives").toMap().value("windows").toString().replace("${arch}",QString::number(QSysInfo::WordSize)))
									  .toMap().value("size").toInt(),
									  libElem.toMap().value("downloads").toMap().value("classifiers").toMap().value(
										  libElem.toMap().value("natives").toMap().value("windows").toString().replace("${arch}",QString::number(QSysInfo::WordSize)))
									  .toMap().value("sha1").toString(),
									  libElem.toMap().value("downloads").toMap().value("classifiers").toMap().value(
										  libElem.toMap().value("natives").toMap().value("windows").toString().replace("${arch}",QString::number(QSysInfo::WordSize)))
									  .toMap().value("path").toString(),
									  libElem.toMap().value("downloads").toMap().value("classifiers").toMap().value(
										  libElem.toMap().value("natives").toMap().value("windows").toString().replace("${arch}",QString::number(QSysInfo::WordSize)))
									  .toMap().value("url").toString()):(
								 libElem.toMap().value("downloads").toMap().contains("artifact")?
									 libUrls<<FileItem(libElem.toMap().value("name").toString(),
													   libElem.toMap().value("downloads").toMap().value("artifact").toMap().value("size").toInt(),
													   libElem.toMap().value("downloads").toMap().value("artifact").toMap().value("sha1").toString(),
													   libElem.toMap().value("downloads").toMap().value("artifact").toMap().value("path").toString(),
													   libElem.toMap().value("downloads").toMap().value("artifact").toMap().value("url").toString()):
									 libUrls);
    });
}

#include "downloadmanager.h"
#include "downloadmanagerplus.h"

QList<FileItem> JsonManager::getDownloadAssertUrls()
{
    QUrl assertUrl=jsonMap.value("assetIndex")
                      .toMap().value("url").toUrl();

	QString filename = corePath+QString("/assets/indexes/%1.json").arg(getAssetIndex());
    jsonDownload->append(FileItem(QString(getAssetIndex()+".json"),
                                  0,
                                  QString(),
                                  filename,
                                  assertUrl));
    jsonDownload->waitForFinished();
    //try{
    qDebug()<<filename;
    QFile f(filename);//!

    QByteArray assertByte;

    if(!f.exists())qDebug()<<"jsonfile(1.10.json) file does not exist";
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))qDebug()<<"Open failed";
    qDebug()<<"jsonfile(1.10.json) file opened!!!";
    assertByte.resize(f.bytesAvailable());
    assertByte = f.readAll();
    f.close();

    QJsonParseError ok;
    auto assertDoc = QJsonDocument::fromJson(assertByte,&ok);
    if(ok.error != QJsonParseError::NoError){qDebug()<<"AssertJson failed."<<endl<<ok.error;}

    auto objectMap = assertDoc.toVariant().toMap().value("objects").toMap();

    QList<FileItem> downloadAssertUrls;

    for(auto it=objectMap.begin();it!=objectMap.end();it++){
        QString name = it.key();
        QString hash = it.value().toMap().value("hash").toString();
        QString path = QString("%1/%2").arg(hash.left(2),hash);
        QUrl url = "http://resources.download.minecraft.net/"+path;
        downloadAssertUrls<<FileItem(name,
                                     it.value().toMap().value("size").toInt(),
                                     "NULL",
                                     path,
                                     url);
    }

    //qDebug()<<"ha?";
    //这个地方不知道为什么“downloadAssertUrls”放循环里正常，外边访问就不对
    //for(auto& i:downloadAssertUrls)
    //    qDebug()<<i.name;
    return downloadAssertUrls;
    //}catch(...){
    //        qDebug()<<"exception";
    //        throw;
    //}
}



QStringList JsonManager::getMCArgs()
{
    return jsonMap.value("minecraftArguments").toString().split(" ");
}



QStringList JsonManager::getMCMainClass()
{
    return jsonMap.value("mainClass").toStringList();
}

QString JsonManager::getAssetIndex()
{
    return jsonMap.value("assets")
            .toString();
}

FileItem JsonManager::getDownloadClientUrl()
{
	return FileItem(jsonMap.value("id").toString()+".jar",
					jsonMap.value("downloads").toMap().value("client").toMap().value("size").toInt(),
					jsonMap.value("downloads").toMap().value("client").toMap().value("sha1").toString(),
					corePath+QString("/versions/%1/%1.jar").arg(jsonMap.value("id").toString()),
					jsonMap.value("downloads").toMap().value("client").toMap().value("url").toString());
}
