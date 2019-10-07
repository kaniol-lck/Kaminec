#include "ModsManager.h"

#include <QList>
#include <cassert>

ModsManager::ModsManager(QObject *parent) : QObject(parent)
{}

bool ModsManager::setGameDir(const QString &gameDir)
{
	usedModsDir_ = gameDir;
	unusedModsDir_ = gameDir;

	if(!usedModsDir_.cd("mods"))
		return false;

	if(!unusedModsDir_.cd("unused_mods")){
		unusedModsDir_.mkdir("unused_mods");
		unusedModsDir_.cd("unused_mods");
	}

	this->refresh();
	return true;
}

QStandardItemModel *ModsManager::getModel()
{
	return &model_;
}

void ModsManager::refresh()
{
	if(!usedModsDir_.exists()){
		return;
	}

	QStringList usedModsFileNames = usedModsDir_.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
	QStringList unusedModsFileNames = unusedModsDir_.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);

	model_.clear();
	model_.setColumnCount(3);
	model_.setHeaderData(0,Qt::Horizontal,"used");
	model_.setHeaderData(1,Qt::Horizontal,"mod name");
	model_.setHeaderData(2,Qt::Horizontal,"mod path");

	for(const auto& fileName : usedModsFileNames){
		if(!fileName.endsWith(".jar") &&
		   !fileName.endsWith(".zip")) continue;

		QList<QStandardItem*> itemList;

		auto checkItem = new QStandardItem();
		checkItem->setCheckable(true);
		checkItem->setCheckState(Qt::Checked);

		auto nameItem = new QStandardItem;
		auto basename(fileName);
		basename.chop(4);
		nameItem->setText(basename);

		auto pathItem = new QStandardItem;
		pathItem->setText(usedModsDir_.filePath(fileName));

		itemList<<checkItem;
		itemList<<nameItem;
		itemList<<pathItem;

		model_.appendRow(itemList);

	}

	for(const auto& fileName : unusedModsFileNames){
		if(!fileName.endsWith(".jar") &&
		   !fileName.endsWith(".zip")) continue;

		QList<QStandardItem*> itemList;

		auto checkItem = new QStandardItem();
		checkItem->setCheckable(true);
		checkItem->setCheckState(Qt::Unchecked);

		auto nameItem = new QStandardItem;
		auto basename(fileName);
		basename.chop(4);
		nameItem->setText(basename);

		auto pathItem = new QStandardItem;
		pathItem->setText(unusedModsDir_.filePath(fileName));

		itemList<<checkItem;
		itemList<<nameItem;
		itemList<<pathItem;

		model_.appendRow(itemList);

	}
	return;

}

void ModsManager::start()
{
	QStringList usedModsFileNames = usedModsDir_.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
	QStringList unusedModsFileNames = unusedModsDir_.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);

	for(int i = 0 ;i < model_.rowCount(); i++ ){
		auto checkItem = model_.item(i, 0);
		auto pathItem = model_.item(i, 2);
		if(checkItem->checkState() == Qt::Checked){
			if(!usedModsFileNames.contains(
				   QFileInfo(pathItem->text()).fileName()))
				move(pathItem->text(),
					 usedModsDir_.filePath(QFileInfo(pathItem->text()).fileName()));
		}else{
			assert(checkItem->checkState() == Qt::Unchecked);
			if(!unusedModsFileNames.contains(
				   QFileInfo(pathItem->text()).fileName()))
				move(pathItem->text(),
					 unusedModsDir_.filePath(QFileInfo(pathItem->text()).fileName()));
		}
	}

	this->refresh();
	return;
}

bool ModsManager::move(const QString &srcFilePath, const QString &tgtFilePath)
{
	if(QFile::copy(srcFilePath, tgtFilePath)){
		QFile(srcFilePath).remove();
		return true;
	}
	else
		return false;
}

