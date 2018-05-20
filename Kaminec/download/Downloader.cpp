#include "Downloader.h"

#include "assistance/Path.h"
#include "messager/DownloadInfo.h"
#include "assistance/Exceptions.h"

#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QStandardItem>

QString Downloader::kVersionManifestDownlaod = "https://launchermeta.mojang.com/mc/game/version_manifest.json";

Downloader::Downloader(QObject *parent) :
	QObject(parent),
	tempFileName_(QDir::tempPath() + "/" +
				 QCoreApplication::applicationName() +"_XXXXXX.json"),
	downloadKit_(new DownloadKit(this))
{}

void Downloader::init()
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
		downloadKit_->append(DownloadInfo(QString("version_manifest.json"),
											0,
											QString("NULL"),
											tempVersionsFile_.fileName(),
											kVersionManifestDownlaod));
		downloadKit_->waitForFinished();

		if(!tempVersionsFile_.open())
			throw FileOpenException(tempVersionsFile_.fileName());

		QByteArray jsonByte;
		jsonByte.resize(tempVersionsFile_.bytesAvailable());
		jsonByte = tempVersionsFile_.readAll();
		tempVersionsFile_.close();

		QJsonParseError ok;
		auto jsonDoc = QJsonDocument::fromJson(jsonByte,&ok);
		if(ok.error != QJsonParseError::NoError)
			throw JsonParseException(tempVersionsFile_.fileName(), ok.errorString(), true);

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

QStandardItemModel *Downloader::getVersionsModel()
{
	return &model_;
}

QStandardItemModel *Downloader::getDownloadModel()
{
	return downloadKit_->getModel();
}

int Downloader::getTotalCount()
{
	return totalCount_;
}

void Downloader::download(int index)
{
	//download json file
	auto version = versionList_.at(index).toMap().value("id").toString();

	downloadKit_->append(DownloadInfo(version + ".json",
									 0,
									 "NULL",
									 QString("%1/%2/%2.json")
									 .arg(Path::versionsPath()).arg(version),
									 versionList_.at(index).toMap().value("url").toUrl()));
	downloadKit_->waitForFinished();

	//download client
	DownloadJson downloadJson(version);

	auto clientDownloadInfo = downloadJson.getClientDownloadInfo();
	clientDownloadInfo.path_.prepend(Path::versionsPath());
	downloadKit_->append(clientDownloadInfo);

	//download libraries
	auto LibraryDownloadInfos = downloadJson.getLibraryDownloadInfos();
	for(auto& item:LibraryDownloadInfos){
		item.path_.prepend(Path::libsPath()+"/");
	}

	downloadKit_->append(LibraryDownloadInfos);

	//download asset index
	auto assetsIndexDownloadInfo = downloadJson.getAssetsIndexDownloadInfo();
	assetsIndexDownloadInfo.path_.prepend(Path::indexesPath());
	downloadKit_->append(assetsIndexDownloadInfo);
	downloadKit_->waitForFinished();

	//download asset objects
	DownloadAssets downloadAsset_(downloadJson.getAssetsIndexId());
	auto downloadAssetUrls = downloadAsset_.getAssetsDownloadInfos();
	for(auto& item : downloadAssetUrls){
		item.path_.append(Path::objectsPath() + "/");
	}
	downloadKit_->append(downloadAssetUrls);

	totalCount_ = downloadKit_->getTotalCount();

	connect(downloadKit_,SIGNAL(downloadedCountChanged(int)),this,SIGNAL(downloadedCountChanged(int)));
	connect(downloadKit_,SIGNAL(finished()),this,SIGNAL(finished()));

	return;
}
