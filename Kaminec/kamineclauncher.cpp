#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "preference.h"
#include "downloadmanager.h"
#include "downloadmanagerplus.h"
#include "JsonManager.h"
#include "assetmanager.h"
#include "gamemode.h"
#include "game.h"
#include "fileitem.h"

#include <algorithm>
#include <QTime>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QSettings>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>
#include <QProcess>
#include <QStandardItemModel>

KaminecLauncher::KaminecLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KaminecLauncher),
	savesManager(this),
	gameDownload(new GameDownload(this)),
	corePath(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).toString())
{
	//setup ui
	ui->setupUi(this);

	//init ui
	ui->versionsList_treeView->setModel(gameDownload->getVersionsModel());
    ui->downloadProgress_label->setVisible(false);
    ui->downloadProgress_progressBar->setVisible(false);
    ui->downloadProgress_progressBar_2->setVisible(false);
    ui->downloadValue_label->setVisible(false);
	ui->saveMgr_treeView->setModel(savesManager.getModel());

	this->loadVersions();

	//load gameDir
	ui->gameDir_le->setText(QSettings().value("gameDir").toString());
}

KaminecLauncher::~KaminecLauncher()
{
	//delete ui
    delete ui;
}

inline const Profile KaminecLauncher::getProfile()
{
	//get current profile
	return Profile(QSettings().value("name").toString(),
				   ui->version_cb->currentText(),
				   ui->gameDir_le->text());
}


void KaminecLauncher::on_start_pb_clicked()
{
	//start game
	this->startGame();
}


void KaminecLauncher::updateDownloadCount(int downloaded)
{
	//update the number in label
    qDebug()<<"changed:"<<downloaded;
	ui->downloadValue_label->setText(QString("%1/%2")
									 .arg(downloaded).arg(totalCount));
}

void KaminecLauncher::downloadFinished()
{
	//slot after download
    ui->download_pb->setText("&Download");
    ui->download_pb->setEnabled(true);
    ui->downloadProgress_label->setVisible(false);
    ui->downloadProgress_progressBar->setVisible(false);
    ui->downloadProgress_progressBar_2->setVisible(false);
	ui->downloadValue_label->setVisible(false);

	//update version select
	ui->version_cb->clear();
	this->loadVersions();
}

void KaminecLauncher::gameFinished()
{
	//slot after playing
    qDebug()<<"finished";
    ui->start_pb->setText("&Start");
    ui->start_pb->setEnabled(true);
}

void KaminecLauncher::on_addSaves_pb_clicked()
{
	//add saves
	savesManager.addSaves();
}

void KaminecLauncher::on_deleteSaves_pb_clicked()
{
	//delete saves
	auto index = ui->saveMgr_treeView->currentIndex();
	savesManager.deleteSaves(index.row());
}

void KaminecLauncher::on_backupSaves_pb_clicked()
{
	//backup saves
	savesManager.backup();
}

void KaminecLauncher::startGame()
{
	//declare a Game instance for launch
	Game *game;

	//judge online or offline
	if(ui->isVerified_cb->isChecked()){
		game = new Game(this,this->getProfile(),Mode::Online);
	}else{
		game = new Game(this,this->getProfile(),Mode::Offline);
	}

	//ui during gaming
	ui->start_pb->setText("Gaming...");
	ui->start_pb->setDisabled(true);
	connect(game,SIGNAL(finished(int)),this,SLOT(gameFinished()));

	//start
	game->start();
}

void KaminecLauncher::on_action_preference_triggered()
{
	//create preference windows
	auto preference =
			new Preference(this);
//	connect(this)
	preference->show();
}


void KaminecLauncher::on_gameDir_showPb_clicked()
{
	auto gameDir = QFileDialog::getExistingDirectory(this,"Please choose the game directory.");
	if(gameDir!=""){
		if(gameDir.endsWith("/.minecraft"))
			ui->gameDir_le->setText(gameDir);
		else
			ui->gameDir_le->setText(gameDir + "/.minecraft");
	}
	return;
}

void KaminecLauncher::on_moduleSwitch_currentChanged(int index)
{
	switch (index) {
	case 1:
		gameDownload->init();
		break;
	default:
		break;
	}
}

void KaminecLauncher::on_download_pb_clicked()
{
	//disable this pushbutton to avoid reclick
	ui->download_pb->setText("Downloading...");
	ui->download_pb->setDisabled(true);

	//some settings during download
	ui->download_treeView->setModel(gameDownload->getDownloadModel());
	ui->downloadValue_label->setText(QString("0/%1").arg(gameDownload->getTotalCount()));
	ui->downloadProgress_progressBar->setMaximum(gameDownload->getTotalCount());
	ui->downloadProgress_progressBar_2->setMaximum(gameDownload->getTotalCount());

	//signals/slots during download and afer download
	connect(gameDownload, SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar,SLOT(setValue(int)));
	connect(gameDownload, SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar_2,SLOT(setValue(int)));
	connect(gameDownload, SIGNAL(finished()),this,SLOT(downloadFinished()));
	//start download game
	gameDownload->download(ui->versionsList_treeView->currentIndex().row());

}

void KaminecLauncher::loadVersions()
{
	//load exsit versions and check laucher_profiles.json
	QDir dir(corePath + "/versions");
	if(dir.exists())
	{
		dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
		QFileInfoList list = dir.entryInfoList();
		for(auto i : list){
			ui->version_cb->addItem(i.fileName());
			if(!profileManager.checkVersion(i.fileName()))
				profileManager.addVersion(i.fileName(), corePath);
		}
	}

	//load last used version
	auto index = ui->version_cb->findText(QSettings().value("lastUsedVersion").toString());
	qDebug()<<QSettings().value("lastUsedVersion").toString();
	if(index != -1)
		ui->version_cb->setCurrentIndex(index);
}
