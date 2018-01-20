#include "AssetsManager.h"

#include "core/Path.h"

#include <QSettings>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QDebug>

QString AssetsManager::resourcesDownload_ = "http://resources.download.minecraft.net/";

AssetsManager::AssetsManager(QObject *parent, QString assetsIndex) :
	QObject(parent),
	corePath_(Path::corePath())
{
	QFile assetsFile(Path::indexesPath() + QString("/%1.json").arg(assetsIndex));

	if(!assetsFile.exists())qDebug()<<"assets file does not exist.";
	if(!assetsFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug()<<"Open assets file failed:"<<assetsIndex;
		return;
	}

	QByteArray assetsBytes;
	assetsBytes.resize(assetsFile.bytesAvailable());
	assetsBytes = assetsFile.readAll();
	assetsFile.close();

	QJsonParseError ok;
	auto assetsDoc = QJsonDocument::fromJson(assetsBytes, &ok);
	if(ok.error != QJsonParseError::NoError)qDebug()<<"assets json failed:"<<ok.error;

	assets_ = assetsDoc.object();
}

QList<FileItem> AssetsManager::getDownloadAssetsUrls()
{
	QList<FileItem> downloadAssetsUrls;

	QJsonObject objects = assets_.value("objects").toObject();
	for(auto it = objects.begin(); it!=objects.end(); it++){
		QString name = it.key();
		int size = it.value().toObject().value("size").toInt();
		QString hash = it.value().toObject().value("hash").toString();
		QString path = QString("%1/%2").arg(hash.left(2), hash);
		QUrl url = resourcesDownload_ + path;
		path.prepend(Path::objectsPath() + "/");

		FileItem downloadAssetsUrl(name, size, "NULL", path, url);
		downloadAssetsUrls<<downloadAssetsUrl;
	}
	return downloadAssetsUrls;
}
