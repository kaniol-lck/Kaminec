#include "JsonManager.h"
#include "fileitem.h"
#include "utility.h"

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
	corePath(QSettings().value("corePath", QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).toString())
{
	QFile jsonFile(corePath + QString("/versions/%1/%1.json").arg(version));

	if(!jsonFile.exists())qDebug()<< "jsonfile file does not exist";
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug()<< "Open failed:" << corePath + QString("/versions/%1/%1.json").arg(version);
		QMessageBox::about(0, "Not find json file", "Json file NOT find,The program will terminate.");
    }
	qDebug()<< "jsonfile(" <<version<< ".json) file opened:" << jsonFile.fileName();

	QByteArray jsonByte;
    jsonByte.resize(jsonFile.bytesAvailable());
    jsonByte = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError ok;
	jsonDoc = QJsonDocument::fromJson(jsonByte, &ok);
	if(ok.error != QJsonParseError::NoError){qDebug()<< "Json failed." << endl << ok.error;}

	jsonContent = jsonDoc.toVariant();
	libList = jsonContent.toMap().value("libraries").toList();
}



QStringList JsonManager::getLibfileList()
{
	QStringList fileList;

	fileList<<std::accumulate(libList.begin(), libList.end(), QStringList(),
							  [this](QStringList libfileList, QVariant libElem){
			  if(libElem.toMap().contains("extract")) return libfileList;
			  if(libElem.toMap().contains("downloads") &&
				 libElem.toMap().value("downloads").toMap().contains("artifact")){
				  libfileList<<value(libElem, "downloads", "artifact", "path")
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

	if(jsonContent.toMap().contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this, jsonContent.toMap().value("inheritsFrom").toString());
		fileList<< inheritedJson->getLibfileList();
	}else {
		fileList<< corePath + QString("/versions/%1/%1.jar").arg(jsonContent.toMap().value("id").toString());
	}

	return fileList;
}



QStringList JsonManager::getExtractfileList()
{
	QStringList fileList;
	fileList<<std::accumulate(libList.begin(), libList.end(), QStringList(),
						   [](QStringList libfileList, QVariant libElem){
		return libElem.toMap().contains("natives")?
				  (value(libElem, "downloads", "classifiers").toMap().contains("natives-windows")?
					   libfileList<< value(libElem, "downloads", "classifiers", "natives-windows", "path").toString():
					   libfileList<< value(libElem, "downloads", "artifact", "path").toString()):
					libfileList;
	});
	if(jsonContent.toMap().contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this, jsonContent.toMap().value("inheritsFrom").toString());
		fileList<< inheritedJson->getExtractfileList();
	}

	return fileList;
}



QList<FileItem> JsonManager::getDownloadLibUrls()
{
	QList<FileItem> downloadLibUrls;
	if(jsonContent.toMap().contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this, jsonContent.toMap().value("inheritsFrom").toString());
		downloadLibUrls<< inheritedJson->getDownloadLibUrls();
	}
	//!!!!!!
	return std::accumulate(libList.begin(), libList.end(), QList<FileItem>(),
						   [this](QList<FileItem> libUrls, QVariant libElem){
		if(jsonContent.toMap().contains("inheritsFrom") &&
		   libElem.toMap().contains("name")){
			auto name = libElem.toMap().value("name").toString().split(":");
			auto filename = QString(name.at(0)).replace('.','/') + "/" +
							name.at(1) + "/" +
							name.at(2) + "/" +
							name.at(1) + "-" +
							name.at(2) + ".jar";
			auto path = corePath + "/libraries/"  + filename;
			auto url = libElem.toMap().value("url").toString() + filename;
			return libUrls<< FileItem(filename, 0, "NULL", path, url);
		}
		return (libElem.toMap().value("downloads").toMap().contains("classifiers") &&
				!value(libElem, "downloads", "classifiers").toMap().contains("test") &&
				libElem.toMap().contains("natives") &&
				libElem.toMap().value("natives").toMap().contains("windows") &&
				value(libElem, "downloads", "classifiers").toMap().contains(
					value(libElem, "natives", "windows").toString()))?
					libUrls<< FileItem(libElem.toMap().value("name").toString(),
									   value(libElem, "downloads", "classifiers",
											value(libElem, "natives", "windows").toString().replace("${arch}",QString::number(QSysInfo::WordSize)),
											"size").toInt(),
									   value(libElem, "downloads", "classifiers",
											value(libElem, "natives", "windows").toString().replace("${arch}",QString::number(QSysInfo::WordSize)),
											"sha1").toString(),
									   value(libElem, "downloads", "classifiers",
											value(libElem, "natives", "windows").toString().replace("${arch}",QString::number(QSysInfo::WordSize)),
											"path").toString(),
									   value(libElem, "downloads", "classifiers",
											 value(libElem, "natives", "windows").toString().replace("${arch}",QString::number(QSysInfo::WordSize)),
											 "url").toString()):(
								 libElem.toMap().value("downloads").toMap().contains("artifact")?
									 libUrls<< FileItem(value(libElem, "name").toString(),
														value(libElem, "downloads", "artifact", "size").toInt(),
														value(libElem, "downloads", "artifact", "sha1").toString(),
														value(libElem, "downloads", "artifact", "path").toString(),
														value(libElem, "downloads", "artifact", "url").toString()):
									 libUrls);
	});
}

FileItem JsonManager::getDownloadAssetFileUrl()
{
	QString filename = getAssetIndex() + ".json";
	int size = value(jsonContent, "assetIndex", "size").toInt();
	QString sha1 = value(jsonContent, "assetIndex", "sha1").toString();
	QString path = corePath + "/assets/indexes/"  + filename;
	QUrl url = value(jsonContent, "assetIndex", "url").toUrl();

	return FileItem(filename, size, sha1, path, url);
}


QStringList JsonManager::getMCArgs()
{
	return jsonContent.toMap().contains("minecraftArguments")?
				jsonContent.toMap().value("minecraftArguments").toString().split(" "):
				jsonContent.toMap().contains("arguments")?
					value(jsonContent, "arguments", "game").toStringList():
					QStringList();
}



QStringList JsonManager::getMCMainClass()
{
	return jsonContent.toMap().value("mainClass").toStringList();
}

QString JsonManager::getAssetIndex()
{
	if(jsonContent.toMap().contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this, jsonContent.toMap().value("inheritsFrom").toString());
		return inheritedJson->getAssetIndex();
	}else {
		return jsonContent.toMap().value("assets").toString();
	}
}

FileItem JsonManager::getDownloadClientUrl()
{
	return FileItem(jsonContent.toMap().value("id").toString()+".jar",
					value(jsonContent, "downloads", "client", "size").toInt(),
					value(jsonContent, "downloads", "client", "sha1").toString(),
					corePath + QString("/versions/%1/%1.jar").arg(jsonContent.toMap().value("id").toString()),
					value(jsonContent, "downloads", "client", "url").toString());
}

