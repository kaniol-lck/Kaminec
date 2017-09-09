#include "gamedownload.h"

#include "fileitem.h"
#include "downloadmanager.h"
#include "downloadmanagerplus.h"
#include "JsonManager.h"
#include "assetmanager.h"

#include <QDebug>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QStandardItem>

GameDownload::GameDownload(QObject *parent) :
	QObject(parent),
	corePath(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).toString()),
	tempFileName(QDir::tempPath() + "/" +
				 QCoreApplication::applicationName() +"_XXXXXX.json"),
	singleDownloader(new DownloadManager(this)),
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

int GameDownload::getTotalCount()
{
	return totalCount;
}

void GameDownload::download(int index)
{
	auto version = versionList.at(index).toMap().value("id").toString();

	singleDownloader->append(FileItem(version + ".json",
									 0,
									 "NULL",
									 QString("%1/versions/%2/%2.json")
									 .arg(corePath).arg(version),
									 versionList.at(index).toMap().value("url").toUrl()));
	singleDownloader->waitForFinished();

	downloadJson = new JsonManager(this,version);

	downloadManagerPlus->append(downloadJson->getDownloadClientUrl());

	auto downloadLibUrls = downloadJson->getDownloadLibUrls();
	for(auto& i:downloadLibUrls){
		i.mPath.prepend(corePath+"/libraries/");
	}

	downloadManagerPlus->append(downloadLibUrls);

	singleDownloader->append(downloadJson->getDownloadAssetFileUrl());
	singleDownloader->waitForFinished();

	downloadAsset = new AssetManager(this,downloadJson->getAssetIndex());
	auto downloadAssetUrls = downloadAsset->getDownloadAssetUrls();
	downloadManagerPlus->append(downloadAssetUrls);

	totalCount = downloadManagerPlus->getTotalCount();

	connect(downloadManagerPlus,SIGNAL(downloadedCountChanged(int)),this,SIGNAL(downloadedCountChanged(int)));
	connect(downloadManagerPlus,SIGNAL(finished()),this,SIGNAL(finished()));

	downloadManagerPlus->waitForFinished();

	return;
}
