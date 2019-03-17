#include "gamedownloaddialog.h"
#include "ui_gamedownloaddialog.h"

#include "download/GameDownload.h"
#include "download/VersionManifestDownload.h"
#include "messenger/GameVersion.h"
#include "download/VersionDownload.h"
#include "download/GameJsonDownload.h"
#include "download/GameClientDownload.h"
#include "download/GameLibrariesDownload.h"
#include "download/AssetIndexDownload.h"
#include "download/AssetObjectsDownload.h"

#include <QDebug>
#include <cassert>

GameDownloadDialog::GameDownloadDialog(QWidget *parent) :
	QDialog(parent),
	ui_(new Ui::GameDownloadDialog),
	gameDownload_(new GameDownload(this))
{
	ui_->setupUi(this);
	reapplyFilter();
	ui_->gameDownload_tableView->setModel(gameDownload_->getModel());
	auto versionManifestDownload = new VersionManifestDownload(this, "<launcher>/version_manifest.json");

	ui_->gameDownload_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//	ui_->gameDownload_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
//	ui_->gameDownload_tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
	ui_->gameDownload_tableView->setColumnWidth(0, 80);
	ui_->gameDownload_tableView->setColumnWidth(1, 80);
//	ui_->gameDownload_tableView->hideColumn(GameDownload::Column::Type);
	ui_->gameDownload_tableView->hideColumn(GameDownload::Column::Time);
	ui_->gameDownload_tableView->hideColumn(GameDownload::Column::ReleaseTime);
	ui_->gameDownload_tableView->hideColumn(GameDownload::Column::Url);

	if(versionManifestDownload->exists()){
		gameDownload_->loadManifest();
	} else{
		connect(versionManifestDownload, &VersionManifestDownload::downloadFinished, gameDownload_, &GameDownload::loadManifest);
		versionManifestDownload->addDownload();
	}

	connect(ui_->enableSnapshot_checkBox, &QCheckBox::stateChanged, this, &GameDownloadDialog::reapplyFilter);
	connect(ui_->enableOldBeta_checkBox, &QCheckBox::stateChanged, this, &GameDownloadDialog::reapplyFilter);
	connect(ui_->enableOldAlpha_checkBox, &QCheckBox::stateChanged, this, &GameDownloadDialog::reapplyFilter);
}

GameDownloadDialog::~GameDownloadDialog()
{
	delete ui_;
}

void GameDownloadDialog::reapplyFilter()
{
	gameDownload_->reapplyFilter(ui_->enableSnapshot_checkBox->isChecked(),
								 ui_->enableOldBeta_checkBox->isChecked(),
								 ui_->enableOldAlpha_checkBox->isChecked());
}

void GameDownloadDialog::on_download_pb_clicked()
{
	auto row = ui_->gameDownload_tableView->currentIndex().row();
	assert(row != -1);
	GameVersion version = gameDownload_->getGameVersion(ui_->gameDownload_tableView->model()->index(row, 0).data().toString());
	qDebug()<<version.versionName();
	auto versionDownload = new VersionDownload(this, version);
	auto downloadFile = [=]{
		if(!versionDownload->gameClientDownload()->exists())
			versionDownload->gameClientDownload()->addDownload();
		if(!versionDownload->gameLibrariesDownload()->exists())
			versionDownload->gameLibrariesDownload()->addDownload();

		auto downloadObjects = [=]{
			if(!versionDownload->assetObjectsDownload()->exists())
				versionDownload->assetObjectsDownload()->addDownload();
		};
		if(!versionDownload->assetIndexDownload()->exists()){
			connect(versionDownload->assetIndexDownload(), &AssetIndexDownload::downloadFinished, [=]{
				versionDownload->loadAssetIndex();
				downloadObjects();
			});
			versionDownload->assetIndexDownload()->addDownload();
		} else
			downloadObjects();
	};
	if(!versionDownload->gameJsonDownload()->exists()){
		connect(versionDownload->gameJsonDownload(), &GameJsonDownload::downloadFinished, [=]{
			versionDownload->loadJson();
			downloadFile();
		});
		versionDownload->gameJsonDownload()->addDownload();
	} else
		downloadFile();
}

void GameDownloadDialog::on_gameDownload_tableView_pressed(const QModelIndex &/*index*/)
{
	ui_->download_pb->setEnabled(true);
}
