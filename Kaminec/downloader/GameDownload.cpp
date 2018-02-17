#include "gamedownload.h"

#include "core/Path.h"
#include "core/json/DownloadAssets.h"
#include "messager/fileitem.h"
#include "downloader/downloadmanagerplus.h"

#include <QDebug>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QStandardItem>

QString GameDownload::kVersionManifestDownlaod = "https://launchermeta.mojang.com/mc/game/version_manifest.json";

GameDownload::GameDownload(QObject *parent) :
	QObject(parent),
	corePath_(Path::corePath()),
	tempFileName_(QDir::tempPath() + "/" +
				 QCoreApplication::applicationName() +"_XXXXXX.json"),
	downloadManagerPlus_(new DownloadManagerPlus(this))
{}

void GameDownload::init()
{
	if(!inited_){
		inited_ = true;

		model_.setColumnCount(5);
		model_.setHeaderData(0,Qt::Horizontal,"id");
		model_.setHeaderData(1,Qt::Horizontal,"type");
		model_.setHeaderData(2,Qt::Horizontal,"time");
		model_.setHeaderData(3,Qt::Horizontal,"releaseTime");
		model_.setHeaderData(4,Qt::Horizontal,"url");

		tempVersionsFile_.open();
		tempVersionsFile_.close();
		downloadManagerPlus_->append(FileItem(QString("version_manifest.json"),
											0,
											QString("NULL"),
											tempVersionsFile_.fileName(),
											kVersionManifestDownlaod));
		downloadManagerPlus_->waitForFinished();

		if(!tempVersionsFile_.open()){
			qDebug()<<"Open failed";
			qDebug()<<"Not find json file,Json file NOT find,The program will terminate.";
		}
		qDebug()<<"versionfile.json file opened";

		QByteArray jsonByte;
		jsonByte.resize(tempVersionsFile_.bytesAvailable());
		jsonByte = tempVersionsFile_.readAll();
		tempVersionsFile_.close();

		QJsonParseError ok;
		auto jsonDoc = QJsonDocument::fromJson(jsonByte,&ok);
		if(ok.error != QJsonParseError::NoError){qDebug()<<"Json failed."<<endl<<ok.error;}

		auto jsonMap = jsonDoc.toVariant().toMap();
		versionList_ = jsonMap.value("versions").toList();

		for(auto i: versionList_)
			model_.appendRow(QList<QStandardItem*>{
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
	return &model_;
}

QStandardItemModel *GameDownload::getDownloadModel()
{
	return downloadManagerPlus_->getModel();
}

int GameDownload::getTotalCount()
{
	return totalCount_;
}

void GameDownload::download(int index)
{
	//download json file
	auto version = versionList_.at(index).toMap().value("id").toString();

	downloadManagerPlus_->append(FileItem(version + ".json",
									 0,
									 "NULL",
									 QString("%1/%2/%2.json")
									 .arg(Path::versionsPath()).arg(version),
									 versionList_.at(index).toMap().value("url").toUrl()));
	downloadManagerPlus_->waitForFinished();

	//download client
	DownloadJson downloadJson(version);

	auto clientFileItem = downloadJson.getClientFileItem();
	clientFileItem.path_.prepend(Path::versionsPath());
	downloadManagerPlus_->append(clientFileItem);

	//download libraries
	auto LibraryFileItems = downloadJson.getLibraryFileItems();
	for(auto& item:LibraryFileItems){
		item.path_.prepend(Path::libsPath()+"/");
	}

	downloadManagerPlus_->append(LibraryFileItems);

	//download asset index
	auto assetsIndexFileItem = downloadJson.getAssetsIndexFileItem();
	assetsIndexFileItem.path_.prepend(Path::indexesPath());
	downloadManagerPlus_->append(assetsIndexFileItem);
	downloadManagerPlus_->waitForFinished();

	//download asset objects
	DownloadAssets downloadAsset_(downloadJson.getAssetsIndexId());
	auto downloadAssetUrls = downloadAsset_.getDownloadAssetsUrls();
	for(auto& item : downloadAssetUrls){
		item.path_.append(Path::objectsPath() + "/");
	}
	downloadManagerPlus_->append(downloadAssetUrls);

	totalCount_ = downloadManagerPlus_->getTotalCount();

	connect(downloadManagerPlus_,SIGNAL(downloadedCountChanged(int)),this,SIGNAL(downloadedCountChanged(int)));
	connect(downloadManagerPlus_,SIGNAL(finished()),this,SIGNAL(finished()));

	return;
}
