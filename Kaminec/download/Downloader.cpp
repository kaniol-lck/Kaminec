#include "Downloader.h"

#include <QFileInfo>
#include <cassert>
#include <algorithm>
#include <QDebug>

Downloader *Downloader::pInstance = nullptr;

void Downloader::init(QObject *parent)
{
	pInstance = new Downloader(parent);
}

Downloader *Downloader::instance()
{
	assert(pInstance != nullptr);
	return pInstance;
}

QStandardItemModel *Downloader::getModel()
{
	return &model_;
}

Downloader::Downloader(QObject *parent) : QObject(parent)
{
	model_.setColumnCount(3);
	model_.setHeaderData(Column::FileName, Qt::Horizontal, tr("File Name"));
	model_.setHeaderData(Column::FileType, Qt::Horizontal, tr("File Type"));
	model_.setHeaderData(Column::Status, Qt::Horizontal, tr("Status"));

	connect(&downloadKit_, &DownloadKit::started, this, [=](QString packName, QString fileName){
		downloadItems_[packName][fileName][Column::Status]->setData(tr("Downloading..."), Qt::DisplayRole);
		auto pack = downloadStatus_[packName];
		pack[fileName] = StatusType::Downloading;
		downloadPackItems_[packName][Column::Status]->setData(tr("Downloading..."), Qt::DisplayRole);
	});
	connect(&downloadKit_, &DownloadKit::finished, this, [=](QString packName, QString fileName){
		downloadItems_[packName][fileName][Column::Status]->setData(tr("Finished"), Qt::DisplayRole);
		auto pack = downloadStatus_[packName];
		pack[fileName] = StatusType::Finished;
		if(std::all_of(pack.begin(), pack.end(), [](StatusType s){return s == StatusType::Finished;})){
			downloadPackItems_[packName][Column::Status]->setData(tr("Finished"), Qt::DisplayRole);
			if(slotFunctions_.contains(packName))
				slotFunctions_.take(packName)();
		}
	});
}

void Downloader::appendDownloadPack(const DownloadPack &downloadPack)
{
	auto nameItem = new QStandardItem(downloadPack.packName());
	auto typeItem = new QStandardItem("");
	auto statusItem = new QStandardItem(tr("Waiting..."));

	for(const auto &info : downloadPack.fileList()){
		QFileInfo fileInfo(info.path());
		if(fileInfo.exists() && (fileInfo.size() != 0)) continue;
		auto items = info2items(info);
		nameItem->appendRow(items);
		downloadItems_[downloadPack.packName()][info.name()] = items;
	}
	QList<QStandardItem *> packItems{ nameItem, typeItem, statusItem };
	downloadPackItems_.insert(downloadPack.packName(), packItems);
	model_.appendRow(packItems);
	downloadStatus_.insert(downloadPack.packName(), downloadPack2map(downloadPack));

	for(auto downloadInfo : downloadPack.fileList())
		downloadKit_.appendDownloadFile(downloadPack.packName(), downloadInfo);
}

void Downloader::appendDownloadPack(const DownloadPack &downloadPack, std::function<void()> slotFuntion)
{
	slotFunctions_.insert(downloadPack.packName(), slotFuntion);
	appendDownloadPack(downloadPack);
}

QList<QStandardItem *> Downloader::info2items(const DownloadInfo &downloadInfo)
{
	return QList<QStandardItem*>{
		new QStandardItem(downloadInfo.name()),
		new QStandardItem(downloadInfo.type()),
		new QStandardItem(tr("Waiting..."))
	};
}

QMap<QString, Downloader::StatusType> Downloader::downloadPack2map(const DownloadPack &downloadPack)
{
	QMap<QString, StatusType> map;
	for(auto info : downloadPack.fileList())
		map.insert(info.name(), StatusType::Waiting);
	return  map;
}
