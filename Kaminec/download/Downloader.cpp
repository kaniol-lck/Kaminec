#include "Downloader.h"

#include "assistance/Path.h"
#include "messager/DownloadInfo.h"
#include "assistance/Exceptions.hpp"
#include "download/DownloadParser.h"

#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QStandardItem>
#include <QDebug>

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

	DownloadParser downloadParser(versionList_, index);

	downloadKit_->append(downloadParser.gameJsonDownloadInfo());
	downloadKit_->waitForFinished();
	downloadParser.loadGameJson();

	//download client
	downloadKit_->append(downloadParser.clientDownloadInfo());

	//download libraries
	downloadKit_->append(downloadParser.libraryDownloadInfos());

	//download asset index
	downloadKit_->append(downloadParser.assetIndexDownloadInfo());
	downloadKit_->waitForFinished();
	downloadParser.loadAssetIndex();

	//download asset objects
	downloadKit_->append(downloadParser.assetObjectDownloadInfos());

	totalCount_ = downloadKit_->getTotalCount();

	connect(downloadKit_,SIGNAL(downloadedCountChanged(int)),this,SIGNAL(downloadedCountChanged(int)));
	connect(downloadKit_,SIGNAL(finished()),this,SIGNAL(finished()));

	return;
}
