#include "modsmanager.h"

#include <QDir>
#include <QDebug>
#include <QList>
#include <cassert>

ModsManager::ModsManager(QObject *parent) : QObject(parent)
{

}

void ModsManager::setGameDir(QString gameDir)
{
	usedModsDir = gameDir;
	unusedModsDir = gameDir;

	if(!usedModsDir.cd("mods"))
		qDebug()<<"haven't launch before";

	if(!unusedModsDir.cd("unused_mods")){
		qDebug()<<"??";
		unusedModsDir.mkdir("unused_mods");
		unusedModsDir.cd("unused_mods");
	}

	this->refresh();
}

QStandardItemModel *ModsManager::getModel()
{
	return &model;
}

void ModsManager::refresh()
{
	if(!usedModsDir.exists()){
		return;
	}

	QStringList usedModsFileNames = usedModsDir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
	QStringList unusedModsFileNames = unusedModsDir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);

	model.clear();
	model.setColumnCount(3);
	model.setHeaderData(0,Qt::Horizontal,"used");
	model.setHeaderData(1,Qt::Horizontal,"mod name");
	model.setHeaderData(2,Qt::Horizontal,"mod path");

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
		pathItem->setText(usedModsDir.filePath(fileName));

		itemList<<checkItem;
		itemList<<nameItem;
		itemList<<pathItem;

		model.appendRow(itemList);

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
		pathItem->setText(unusedModsDir.filePath(fileName));

		itemList<<checkItem;
		itemList<<nameItem;
		itemList<<pathItem;

		model.appendRow(itemList);

	}
	return;

}

void ModsManager::start()
{
	QStringList usedModsFileNames = usedModsDir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
	QStringList unusedModsFileNames = unusedModsDir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);

	for(int i = 0 ;i < model.rowCount(); i++ ){
		auto checkItem = model.item(i, 0);
		auto pathItem = model.item(i, 2);
		if(checkItem->checkState() == Qt::Checked){
			if(!usedModsFileNames.contains(
				   QFileInfo(pathItem->text()).fileName()))
				move(pathItem->text(),
					 usedModsDir.filePath(QFileInfo(pathItem->text()).fileName()));
		}else{
			assert(checkItem->checkState() == Qt::Unchecked);
			if(!unusedModsFileNames.contains(
				   QFileInfo(pathItem->text()).fileName()))
				move(pathItem->text(),
					 unusedModsDir.filePath(QFileInfo(pathItem->text()).fileName()));
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

