#include "modsmanager.h"

#include <QDir>
#include <QDebug>
#include <QList>

ModsManager::ModsManager(QObject *parent) : QObject(parent)
{

}

void ModsManager::setGameDir(QString gameDir)
{
	modsDir = gameDir;
	modsDir.cd("mods");
	this->refresh();
}

QStandardItemModel *ModsManager::getModel()
{
	return &model;
}

void ModsManager::refresh()
{
	if(!modsDir.exists()){
		return;
	}

	QStringList fileNames = modsDir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);

	model.clear();
	model.setColumnCount(3);
	model.setHeaderData(0,Qt::Horizontal,"used");
	model.setHeaderData(1,Qt::Horizontal,"mod name");
	model.setHeaderData(2,Qt::Horizontal,"mod path");

	for(const auto& fileName : fileNames){
		if(!fileName.endsWith(".jar")) continue;

		QList<QStandardItem*> itemList;

		auto checkItem = new QStandardItem;
		checkItem->setCheckable(true);

		auto nameItem = new QStandardItem;
		auto basename(fileName);
		basename.chop(4);
		nameItem->setText(basename);

		auto pathItem = new QStandardItem;
		pathItem->setText(modsDir.absolutePath() + fileName);

		itemList<<checkItem;
		itemList<<nameItem;
		itemList<<pathItem;

		model.appendRow(itemList);

	}
	return;

}

