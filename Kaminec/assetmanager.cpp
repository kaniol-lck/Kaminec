#include "assetmanager.h"

#include <QSettings>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QDebug>

AssetManager::AssetManager(QObject *parent, QString assetIndex) :
	QObject(parent),
	corePath(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).toString())
{
	QFile assetFile(corePath+QString("/assets/indexes/%1.json").arg(assetIndex));

	if(!assetFile.exists())qDebug()<<"asset file does not exist.";
	if(!assetFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug()<<"Open asset file failed:"<<assetIndex;
		return;
	}

	QByteArray assetBytes;
	assetBytes.resize(assetFile.bytesAvailable());
	assetBytes = assetFile.readAll();
	assetFile.close();

	QJsonParseError ok;
	auto assetDoc = QJsonDocument::fromJson(assetBytes,&ok);
	if(ok.error != QJsonParseError::NoError)qDebug()<<"asset json failed:"<<ok.error;

	asset = assetDoc.object();
}

QList<FileItem> AssetManager::getDownloadAssetUrls()
{
	QList<FileItem> downloadAssetUrls;

	QJsonObject objects = asset.value("objects").toObject();
	for(auto it = objects.begin(); it!=objects.end(); it++){
		QString name = it.key();
		int size = it.value().toObject().value("size").toInt();
		QString hash = it.value().toObject().value("hash").toString();
		QString path = QString("%1/%2").arg(hash.left(2),hash);
		QUrl url = "http://resources.download.minecraft.net/" + path;
		path.prepend(corePath + "/");

		FileItem downloadAssetUrl(name,size,"NULL",path,url);
		downloadAssetUrls<<downloadAssetUrl;
	}
	return downloadAssetUrls;
}
