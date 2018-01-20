#include "JsonManager.h"
#include "core/Path.h"
#include "messager/fileitem.h"
#include "assistance/utility.h"
#include "assistance/systeminfo.h"

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
	jsonDownload_(new DownloadManagerPlus(this)),
	corePath_(Path::corePath())
{
	QFile jsonFile(Path::versionsPath() + QString("/%1/%1.json").arg(version));

	if(!jsonFile.exists())qDebug()<< "jsonfile file does not exist";
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug()<< "Open failed:" << jsonFile.fileName();
		QMessageBox::about(0, "Not find json file", "Json file NOT find,The program will terminate.");
    }
	qDebug()<< "jsonfile(" <<version<< ".json) file opened:" << jsonFile.fileName();

	QByteArray jsonByte;
    jsonByte.resize(jsonFile.bytesAvailable());
    jsonByte = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError ok;
	jsonDoc_ = QJsonDocument::fromJson(jsonByte, &ok);
	if(ok.error != QJsonParseError::NoError){qDebug()<< "Json failed." << endl << ok.error;}

	jsonContent_ = jsonDoc_.toVariant();
	libList_ = jsonContent_.toMap().value("libraries").toList();
}

QStringList JsonManager::getLibfileList()
{
	QStringList fileList;

	fileList<<std::accumulate(libList_.begin(), libList_.end(), QStringList(),
							  [this](QStringList libfileList, QVariant libElem){
			  if(libElem.toMap().contains("natives")) return libfileList;
				  auto filename = genFilename(libElem.toMap().value("name").toString());
				  libfileList<<filename.prepend(Path::libsPath() + "/");
				 return libfileList;
			 });

	if(jsonContent_.toMap().contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this, jsonContent_.toMap().value("inheritsFrom").toString());
		fileList<< inheritedJson->getLibfileList();
	}else {
		fileList<< Path::versionsPath() + QString("/%1/%1.jar").arg(jsonContent_.toMap().value("id").toString());
	}

	return fileList;
}

QStringList JsonManager::getExtractfileList()
{
	QStringList fileList;
	fileList<<std::accumulate(libList_.begin(), libList_.end(), QStringList(),
						   [](QStringList libfileList, QVariant libElem){
		return libElem.toMap().contains("natives") &&
			  libElem.toMap().value("natives").toMap().contains(sysName())?
					   libfileList<< value(libElem, "downloads", "classifiers",
										   value(libElem, "natives", sysName())
										   .toString().replace("${arch}", QString::number(sysWordSize())), "path").toString():
					libfileList;
	});
	if(jsonContent_.toMap().contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this, jsonContent_.toMap().value("inheritsFrom").toString());
		fileList<< inheritedJson->getExtractfileList();
	}

	return fileList;
}

QList<FileItem> JsonManager::getDownloadLibUrls()
{
	QList<FileItem> downloadLibUrls;
	if(jsonContent_.toMap().contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this, jsonContent_.toMap().value("inheritsFrom").toString());
		downloadLibUrls<< inheritedJson->getDownloadLibUrls();
	}

	return std::accumulate(libList_.begin(), libList_.end(), QList<FileItem>(),
						   [this](QList<FileItem> libUrls, QVariant libElem){
		if(jsonContent_.toMap().contains("inheritsFrom") &&
		   libElem.toMap().contains("name")){
			auto filename = genFilename(libElem.toMap().value("name").toString());
			auto path = Path::libsPath() + "/"  + filename;
			auto url = libElem.toMap().value("url").toString() + filename;
			return libUrls<< FileItem(filename, 0, "NULL", path, url);
		}
		return (libElem.toMap().value("downloads").toMap().contains("classifiers") &&
				!value(libElem, "downloads", "classifiers").toMap().contains("test") &&
				libElem.toMap().contains("natives") &&
				libElem.toMap().value("natives").toMap().contains(sysName()) &&
				value(libElem, "downloads", "classifiers").toMap().contains(
					value(libElem, "natives", sysName()).toString()))?
					libUrls<< FileItem::fromJson(libElem.toMap().value("name").toString(),
												 value(libElem, "downloads", "classifiers",
													   value(libElem, "natives", sysName())
													   .toString().replace("${arch}", QString::number(sysWordSize())))):(
								  libElem.toMap().value("downloads").toMap().contains("artifact")?
									  libUrls<< FileItem::fromJson(value(libElem, "name").toString(),
																   value(libElem, "downloads", "artifact")):
									  libUrls);
	});
}

FileItem JsonManager::getDownloadAssetsFileUrl()
{
	QString filename = getAssetsIndex() + ".json";
	int size = value(jsonContent_, "assetIndex", "size").toInt();
	QString sha1 = value(jsonContent_, "assetIndex", "sha1").toString();
	QString path = Path::indexesPath() + "/"  + filename;
	QUrl url = value(jsonContent_, "assetIndex", "url").toUrl();

	return FileItem(filename, size, sha1, path, url);
}

QStringList JsonManager::getGameArgs()
{
	return jsonContent_.toMap().contains("minecraftArguments")?
				jsonContent_.toMap().value("minecraftArguments").toString().split(" "):
				jsonContent_.toMap().contains("arguments")?
					value(jsonContent_, "arguments", "game").toStringList():
					QStringList();
}

QStringList JsonManager::getGameMainClass()
{
	return jsonContent_.toMap().value("mainClass").toStringList();
}

QStringList JsonManager::getJVMArgs()
{
	/*This function uses ONLY in version above 1.13*/
	return jsonContent_.toMap().contains("arguments")?
				value(jsonContent_, "arguments", "jvm").toStringList():
				QStringList();
}

QString JsonManager::getAssetsIndex()
{
	if(jsonContent_.toMap().contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this, jsonContent_.toMap().value("inheritsFrom").toString());
		return inheritedJson->getAssetsIndex();
	}else {
		return jsonContent_.toMap().value("assets").toString();
	}
}

FileItem JsonManager::getDownloadClientUrl()
{
	return FileItem(jsonContent_.toMap().value("id").toString()+".jar",
					value(jsonContent_, "downloads", "client", "size").toInt(),
					value(jsonContent_, "downloads", "client", "sha1").toString(),
					Path::versionsPath() + QString("/%1/%1.jar").arg(jsonContent_.toMap().value("id").toString()),
					value(jsonContent_, "downloads", "client", "url").toString());
}

QStringList JsonManager::getVersionChain()
{
	if(jsonContent_.toMap().contains("inheritsFrom")){
		auto inheritedJson = new JsonManager(this, jsonContent_.toMap().value("inheritsFrom").toString());
		return jsonContent_.toMap().value("id").toStringList() +
				inheritedJson->getVersionChain();
	} else{
		return jsonContent_.toMap().value("id").toStringList();
	}
}
