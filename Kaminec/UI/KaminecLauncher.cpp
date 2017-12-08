#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "preference.h"
#include "downloadmanagerplus.h"
#include "JsonManager.h"
#include "assetmanager.h"
#include "gamemode.h"
#include "game.h"
#include "fileitem.h"
#include "modsmanager.h"

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
	savesManager(new SavesManager(this)),
	modsManager(new ModsManager(this)),
	gameDownload(new GameDownload(this)),
	corePath(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).toString())
{
	//setup ui
	ui->setupUi(this);

	//init ui
	ui->modsMgr_treeView->setModel(modsManager->getModel());
    ui->downloadProgress_label->setVisible(false);
    ui->downloadProgress_progressBar->setVisible(false);
    ui->downloadProgress_progressBar_2->setVisible(false);
    ui->downloadValue_label->setVisible(false);
	ui->saveMgr_treeView->setModel(savesManager->getModel());
	ui->moduleSwitch->setStyleSheet("QTabWidget::pane {border-top:0px solid #e8f3f9;background:  transparent; }\
									QTabBar::tab {min-width:100px;color: white;border: 0px solid;border-top-left-radius: 0px;border-top-right-radius: 0px;padding:3px;}\
									QTabBar::tab:!selected {color: gray; margin-top: 5px; background-color: rgb(255,255,255,200)} \
									QTabBar::tab:selected {color: black; border: 1px solid; background-color: rgb(255,255,255,255)}");
	this->loadVersions();

	//load gameDir
	ui->gameDir_le->setText(QSettings().value("gameDir").toString());
	ui->isVerified_cb->setChecked(QSettings().value("isOnline", false).toBool());

	modsManager->setGameDir(ui->gameDir_le->text());
	ui->versionsList_treeView->setModel(gameDownload->getVersionsModel());
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
	this->updateVersionSelect();
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
	savesManager->addSaves();
}

void KaminecLauncher::on_deleteSaves_pb_clicked()
{
	//delete saves
	auto index = ui->saveMgr_treeView->currentIndex();
	savesManager->deleteSaves(index.row());
}

void KaminecLauncher::on_backupSaves_pb_clicked()
{
	//backup saves
	savesManager->backup();
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

	//prepare mods
	modsManager->start();

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
	auto preference = new Preference(this);
	preference->show();

	connect(preference,SIGNAL(accepted()),this,SLOT(updateVersionSelect()));
}


void KaminecLauncher::on_gameDir_showPb_clicked()
{
	//ask for game directory
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
	//if you click the page of game download,
	//download game version list
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

void KaminecLauncher::setBackGround()
{
	//set backGround
	QPixmap pixmap = QPixmap(":/main/res/background.png").scaled(this->size());
	QPalette palette(this->palette());
	palette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette(palette);
}

void KaminecLauncher::updateVersionSelect()
{
	ui->version_cb->clear();
	corePath = QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).toString();
	this->loadVersions();
}

void KaminecLauncher::resizeEvent(QResizeEvent *)
{
	//reset background when resize this window
	setBackGround();
}
