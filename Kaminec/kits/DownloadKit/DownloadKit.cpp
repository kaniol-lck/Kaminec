#include "DownloadKit.h"

#include <QFileInfo>
#include <QEventLoop>
#include <QDebug>
#include <cassert>

DownloadKit *DownloadKit::pInstance = nullptr;

DownloadKit::DownloadKit(QObject *parent) : QObject(parent)
{
	for(int index = 0; index!= downloadNumber_; ++index){
		downloaderPool_.append(new SingleDownload(this,&manager_));
		connect(downloaderPool_.at(index), &SingleDownload::finished, this, &DownloadKit::singleFinished);
		//once downloader finished and start next download
	}
	model_.setColumnCount(3);
	model_.setHeaderData(Column::FileName, Qt::Horizontal, tr("File Name"));
	model_.setHeaderData(Column::FileType, Qt::Horizontal, tr("File Type"));
	model_.setHeaderData(Column::Status, Qt::Horizontal, tr("Status"));
}

void DownloadKit::init(QObject *parent)
{
	pInstance = new DownloadKit(parent);
}

DownloadKit *DownloadKit::instance()
{
	assert(pInstance != nullptr);
	return pInstance;
}

void DownloadKit::appendDownloadPack(const DownloadPack &downloadPack)
{
	for(auto downloadInfo : downloadPack.fileList()){
		QFileInfo fileInfo(downloadInfo.path());
		//download only if file does not exist or has empty size(download failed)
		if(!fileInfo.exists() || (fileInfo.size() == 0))
			downloadInfoQueue_.enqueue(downloadInfo);
		spur();
	}

	auto list = downloadPack.toRowList();
	auto packItem = list.takeFirst();
	for(auto rowItems : list){
		downloadRowQueue_.enqueue(rowItems);
		model_.appendRow(rowItems);
		auto childItem = rowItems.first();
		packItem.first()->setChild(childItem->row(), childItem);
	}
}

void DownloadKit::appendDownloadPack(const DownloadPack &downloadPack, std::function<void()> slotFuntion)
{
	appendDownloadPack(downloadPack);
	slotFunctions.insert(downloadPack.packName(), slotFuntion);
}

QStandardItemModel *DownloadKit::getModel()
{
	return &model_;
}

void DownloadKit::spur()
{
	for(auto singleDownloader : downloaderPool_){
		if(downloadInfoQueue_.isEmpty()||downloadRowQueue_.isEmpty()) break;
		if(!singleDownloader->isOccupied())
			singleDownloader->start(downloadInfoQueue_.dequeue(), downloadRowQueue_.dequeue());
	}
}

void DownloadKit::singleFinished(int row)
{
	qDebug()<<"downloader finished,next";

	if(downloadInfoQueue_.empty()){
		bool noTask = true;
		for(auto downloader: downloaderPool_){
			if(downloader->isOccupied()){
				noTask = false;
				break;
			}
		}
		if(noTask){
			qDebug()<<"All finished.";
			emit finished();
		}
		return;
	}
	bool downloadedAll = true;
	auto parent = model_.item(row, 0)->parent();
	for(auto child : model_.findItems("", Qt::MatchRecursive)){
		if(child->parent() == parent &&
		   model_.item(child->row(), Column::Status)->data(Qt::DisplayRole) == tr("Status")){
			downloadedAll = false;
			break;
		}
	}
	if(downloadedAll)
		slotFunctions.take(parent->data(Qt::DisplayRole).toString());

	spur();
}
