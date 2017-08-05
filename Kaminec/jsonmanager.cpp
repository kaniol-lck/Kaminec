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
	QStringList fileList;
	if(jsonMap.contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this,jsonMap.value("inheritsFrom").toString());
		fileList<<inheritedJson->getLibfileList();
	}else {
		fileList<<corePath + QString("/versions/%1/%1.jar")
					 .arg(jsonMap.value("id").toString());
	}

	fileList<<std::accumulate(libList.begin(),libList.end(),QStringList(),
									[this](QStringList libfileList,QVariant libElem){
				  if(libElem.toMap().contains("downloads") &&
					 libElem.toMap().value("downloads").toMap().contains("artifact")){
					  libfileList<<libElem.toMap().value("downloads")
								   .toMap().value("artifact")
								   .toMap().value("path")
								   .toString().prepend(corePath + "/libraries/");
				  }else if (libElem.toMap().contains("name")) {
					 auto name = libElem.toMap().value("name").toString().split(":");
					 auto filename = QString(name.at(0)).replace('.','/') + "/" +
									 name.at(1) + "/" +
									 name.at(2) + "/" +
									 name.at(1) + "-" +
									 name.at(2) + ".jar";
					 libfileList<<filename.prepend(corePath + "/libraries/");
				 }
				 return libfileList;
			 });
	return fileList;
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

FileItem JsonManager::getDownloadAssetFileUrl()
{
	QString filename =getAssetIndex() + ".json";
	int size = jsonMap.value("assetIndex").toMap().value("size").toInt();
	QString sha1 = jsonMap.value("assetIndex").toMap().value("sha1").toString();
	QString path = corePath + "/assets/indexes/"  + filename;
	QUrl url = jsonMap.value("assetIndex").toMap().value("url").toUrl();

	return FileItem(filename, size, sha1, path, url);
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
	if(jsonMap.contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this,jsonMap.value("inheritsFrom").toString());
		return inheritedJson->getAssetIndex();
	}else {
		return jsonMap.value("assets")
				.toString();
	}
}

FileItem JsonManager::getDownloadClientUrl()
{
	return FileItem(jsonMap.value("id").toString()+".jar",
					jsonMap.value("downloads").toMap().value("client").toMap().value("size").toInt(),
					jsonMap.value("downloads").toMap().value("client").toMap().value("sha1").toString(),
					corePath+QString("/versions/%1/%1.jar").arg(jsonMap.value("id").toString()),
					jsonMap.value("downloads").toMap().value("client").toMap().value("url").toString());
}
