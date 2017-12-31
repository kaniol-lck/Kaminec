#include "gamedownload.h"

#include "core/Path.h"
#include "core/JsonManager.h"
#include "core/AssetsManager.h"
#include "messager/fileitem.h"
#include "downloader/downloadmanagerplus.h"

#include <QDebug>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QStandardItem>

GameDownload::GameDownload(QObject *parent) :
	QObject(parent),
	corePath(Path::corePath()),
	tempFileName(QDir::tempPath() + "/" +
				 QCoreApplication::applicationName() +"_XXXXXX.json"),
	downloadManagerPlus(new DownloadManagerPlus(this))
{}

void GameDownload::init()
{
	if(!inited){
		inited = true;

		model.setColumnCount(5);
		model.setHeaderData(0,Qt::Horizontal,"id");
		model.setHeaderData(1,Qt::Horizontal,"type");
		model.setHeaderData(2,Qt::Horizontal,"time");
		model.setHeaderData(3,Qt::Horizontal,"releaseTime");
		model.setHeaderData(4,Qt::Horizontal,"url");

		tempVersionsFile.open();
		tempVersionsFile.close();
		downloadManagerPlus->append(FileItem(QString("version_manifest.json"),
											0,
											QString("NULL"),
											tempVersionsFile.fileName(),
											QUrl("https://launchermeta.mojang.com/mc/game/version_manifest.json")));
		downloadManagerPlus->waitForFinished();

		if(!tempVersionsFile.open()){
			qDebug()<<"Open failed";
			qDebug()<<"Not find json file,Json file NOT find,The program will terminate.";
		}
		qDebug()<<"versionfile.json file opened";

		QByteArray jsonByte;
		jsonByte.resize(tempVersionsFile.bytesAvailable());
		jsonByte = tempVersionsFile.readAll();
		tempVersionsFile.close();

		QJsonParseError ok;
		auto jsonDoc = QJsonDocument::fromJson(jsonByte,&ok);
		if(ok.error != QJsonParseError::NoError){qDebug()<<"Json failed."<<endl<<ok.error;}

		auto jsonMap = jsonDoc.toVariant().toMap();
		versionList = jsonMap.value("versions").toList();

		for(auto i: versionList)
			model.appendRow(QList<QStandardItem*>{
								new QStandardItem(i.toMap().value("id").toString()),
								new QStandardItem(i.toMap().value("type").toString()),
								new QStandardItem(i.toMap().value("time").toString()),
								new QStandardItem(i.toMap().value("releaseTime").toString()),
								new QStandardItem(i.toMap().value("url").toString())
							});
	}
}

QStandardItemModel *GameDownload::getVersionsModel()
{
	return &model;
}

QStandardItemModel *GameDownload::getDownloadModel()
{
	return downloadManagerPlus->getModel();
}

int GameDownload::getTotalCount()
{
	return totalCount;
}

void GameDownload::download(int index)
{
	auto version = versionList.at(index).toMap().value("id").toString();

	downloadManagerPlus->append(FileItem(version + ".json",
									 0,
									 "NULL",
									 QString("%1/%2/%2.json")
									 .arg(Path::versionsPath()).arg(version),
									 versionList.at(index).toMap().value("url").toUrl()));
	downloadManagerPlus->waitForFinished();

	downloadJson = new JsonManager(this, version);

	downloadManagerPlus->append(downloadJson->getDownloadClientUrl());

	auto downloadLibUrls = downloadJson->getDownloadLibUrls();
	for(auto& i:downloadLibUrls){
		i.mPath.prepend(Path::libsPath()+"/");
	}

	downloadManagerPlus->append(downloadLibUrls);

	downloadManagerPlus->append(downloadJson->getDownloadAssetsFileUrl());
	downloadManagerPlus->waitForFinished();

	downloadAsset = new AssetsManager(this,downloadJson->getAssetsIndex());
	auto downloadAssetUrls = downloadAsset->getDownloadAssetsUrls();
	downloadManagerPlus->append(downloadAssetUrls);

	totalCount = downloadManagerPlus->getTotalCount();

	connect(downloadManagerPlus,SIGNAL(downloadedCountChanged(int)),this,SIGNAL(downloadedCountChanged(int)));
	connect(downloadManagerPlus,SIGNAL(finished()),this,SIGNAL(finished()));

	return;
}
