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

	connect(&downloadKit_, &DownloadKit::finished, this, [=](QString packName, QString fileName){
		auto pack = downloadStatus_[packName];
		pack[fileName] = true;
		if(std::all_of(pack.begin(), pack.end(), [](bool b){return b;})){
			if(slotFunctions_.contains(packName))
				slotFunctions_.take(packName)();
		}
	});
}

void Downloader::appendDownloadPack(const DownloadPack &downloadPack)
{
	for(auto downloadInfo : downloadPack.fileList()){
		downloadKit_.appendDownloadFile(downloadPack.packName(), downloadInfo);
	}
	model_.appendRow(downloadPack2items(downloadPack));
	downloadStatus_.insert(downloadPack.packName(), downloadPack2map(downloadPack));
}

void Downloader::appendDownloadPack(const DownloadPack &downloadPack, std::function<void()> slotFuntion)
{
	slotFunctions_.insert(downloadPack.packName(), slotFuntion);
	appendDownloadPack(downloadPack);
}

QList<QStandardItem *> Downloader::downloadPack2items(const DownloadPack &downloadPack)
{
	auto nameItem = new QStandardItem(downloadPack.packName());
	auto typeItem = new QStandardItem("");
	auto statusItem = new QStandardItem(tr("Waiting"));

	for(auto info : downloadPack.fileList()){
		QFileInfo fileInfo(info.path());
		if(fileInfo.exists() && (fileInfo.size() != 0)) continue;
		nameItem->appendRow(QList<QStandardItem*>{
								new QStandardItem(info.name()),
								new QStandardItem(info.type()),
								new QStandardItem(tr("Waiting"))
							});
	}

	return { nameItem, typeItem, statusItem };
}

QMap<QString, bool> Downloader::downloadPack2map(const DownloadPack &downloadPack)
{
	QMap<QString, bool> map;
	for(auto info : downloadPack.fileList())
		map.insert(info.name(), false);
	return  map;
}
