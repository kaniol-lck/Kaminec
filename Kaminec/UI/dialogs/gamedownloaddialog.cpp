#include "gamedownloaddialog.h"
#include "ui_gamedownloaddialog.h"

#include "download/VersionManifestDownload.h"
#include "exception/Exceptions.hpp"
#include "assistance/PathReplacer.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>

GameDownloadDialog::GameDownloadDialog(QWidget *parent) :
	QDialog(parent),
	ui_(new Ui::GameDownloadDialog)
{
	ui_->setupUi(this);
	proxyModel_.setSourceModel(&model_);
	reapplyFilter();
	proxyModel_.setFilterKeyColumn(Column::Type);
	ui_->gameDownload_tableView->setModel(&proxyModel_);
	auto versionManifestDownload = new VersionManifestDownload(this, "<launcher>/version_manifest.json");

	model_.setColumnCount(5);
	model_.setHeaderData(0,Qt::Horizontal, tr("Version Id"));
	model_.setHeaderData(1,Qt::Horizontal, tr("Type"));
	model_.setHeaderData(2,Qt::Horizontal, tr("Time"));
	model_.setHeaderData(3,Qt::Horizontal, tr("Release Time"));
	model_.setHeaderData(4,Qt::Horizontal, tr("Url"));

	ui_->gameDownload_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//	ui_->gameDownload_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
//	ui_->gameDownload_tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
	ui_->gameDownload_tableView->setColumnWidth(0, 80);
	ui_->gameDownload_tableView->setColumnWidth(1, 80);
//	ui_->gameDownload_tableView->hideColumn(Column::Type);
	ui_->gameDownload_tableView->hideColumn(Column::Time);
	ui_->gameDownload_tableView->hideColumn(Column::ReleaseTime);
	ui_->gameDownload_tableView->hideColumn(Column::Url);

	if(versionManifestDownload->exists())
		loadVersions();
	else{
		connect(versionManifestDownload, &VersionManifestDownload::downloadFinished, this, &GameDownloadDialog::loadVersions);
		versionManifestDownload->AddDownload();
	}

	connect(ui_->enableSnapshot_checkBox, &QCheckBox::stateChanged, this, &GameDownloadDialog::reapplyFilter);
	connect(ui_->enableOldBeta_checkBox, &QCheckBox::stateChanged, this, &GameDownloadDialog::reapplyFilter);
	connect(ui_->enableOldAlpha_checkBox, &QCheckBox::stateChanged, this, &GameDownloadDialog::reapplyFilter);
}

void GameDownloadDialog::loadVersions()
{
	QFile file(PathReplacer::replace("<launcher>/version_manifest.json"));
	if(!file.open(QIODevice::ReadOnly))
		throw FileOpenException(file.fileName());

	QByteArray jsonByte;
	jsonByte.resize(static_cast<int>(file.bytesAvailable()));
	jsonByte = file.readAll();
	file.close();

	QJsonParseError ok;
	auto jsonDoc = QJsonDocument::fromJson(jsonByte,&ok);
	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(file.fileName(), ok.errorString(), true);

	auto versionList = jsonDoc.toVariant().toMap().value("versions").toList();
	for(auto i: versionList)
		model_.appendRow(QList<QStandardItem*>{
							 new QStandardItem(i.toMap().value("id").toString()),
							 new QStandardItem(i.toMap().value("type").toString()),
							 new QStandardItem(i.toMap().value("time").toString()),
							 new QStandardItem(i.toMap().value("releaseTime").toString()),
							 new QStandardItem(i.toMap().value("url").toString())
						 });
}

GameDownloadDialog::~GameDownloadDialog()
{
	delete ui_;
}

void GameDownloadDialog::reapplyFilter()
{
	QString str = "(release)";
	if(ui_->enableSnapshot_checkBox->isChecked())
		str.append("|(snapshot)");
	if(ui_->enableOldBeta_checkBox->isChecked())
		str.append("|(old_beta)");
	if(ui_->enableOldAlpha_checkBox->isChecked())
		str.append("|(old_alpha)");
	proxyModel_.setFilterRegExp(QRegExp(str));
}
