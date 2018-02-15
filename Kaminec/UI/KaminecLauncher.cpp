#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "UI/Preference.h"
#include "core/Path.h"
#include "core/gamemode.h"
#include "core/NewGame.h"
#include "LAminec/modsmanager.h"
#include "LAminec/savesmanager.h"
#include "downloader/downloadmanagerplus.h"

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
    ui_(new Ui::KaminecLauncher),
	activeAuth_(new ActiveAuth(this)),
	savesManager_(new SavesManager(this)),
	modsManager_(new ModsManager(this)),
	gameDownload_(new GameDownload(this)),
	corePath_(Path::corePath())
{
	//setup ui
	ui_->setupUi(this);

	//init ui
	ui_->modsMgr_treeView->setModel(modsManager_->getModel());
    ui_->downloadProgress_label->setVisible(false);
    ui_->downloadProgress_progressBar->setVisible(false);
    ui_->downloadProgress_progressBar_2->setVisible(false);
    ui_->downloadValue_label->setVisible(false);
	ui_->saveMgr_treeView->setModel(savesManager_->getModel());

	this->loadVersions();

	//load gameDir
	ui_->gameDir_le->setText(QSettings().value("gameDir").toString());
	ui_->isVerified_cb->setChecked(QSettings().value("isOnline", false).toBool());

	modsManager_->setGameDir(ui_->gameDir_le->text());
	ui_->versionsList_treeView->setModel(gameDownload_->getVersionsModel());
}

KaminecLauncher::~KaminecLauncher()
{
	//delete ui
    delete ui_;
}

inline const Profile KaminecLauncher::getProfile()
{
	//get current profile
	return Profile(QSettings().value("name").toString(),
				   ui_->version_cb->currentText(),
				   ui_->gameDir_le->text());
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
	ui_->downloadValue_label->setText(QString("%1/%2")
									 .arg(downloaded).arg(totalCount_));
}

void KaminecLauncher::downloadFinished()
{
	//slot after download
    ui_->download_pb->setText("&Download");
    ui_->download_pb->setEnabled(true);
    ui_->downloadProgress_label->setVisible(false);
    ui_->downloadProgress_progressBar->setVisible(false);
    ui_->downloadProgress_progressBar_2->setVisible(false);
	ui_->downloadValue_label->setVisible(false);

	//update version select
	this->updateVersionSelect();
}

void KaminecLauncher::gameFinished()
{
	//slot after playing
    qDebug()<<"finished";
    ui_->start_pb->setText("&Start");
    ui_->start_pb->setEnabled(true);
}

void KaminecLauncher::on_addSaves_pb_clicked()
{
	//add saves
	savesManager_->addSaves();
}

void KaminecLauncher::on_deleteSaves_pb_clicked()
{
	//delete saves
	auto index = ui_->saveMgr_treeView->currentIndex();
	savesManager_->deleteSaves(index.row());
}

void KaminecLauncher::on_backupSaves_pb_clicked()
{
	//backup saves
	savesManager_->backup();
}

void KaminecLauncher::startGame()
{
	//declare a Auth for game
	LaunchAuth auth(ui_->isVerified_cb->isChecked()?
						Mode::Online :
						Mode::Offline);

	//prepare mods
	modsManager_->start();

	//init game
	auto game = new Game(this, this->getProfile(), auth);

	//ui during gaming
	ui_->start_pb->setText("Gaming...");
	ui_->start_pb->setDisabled(true);
	connect(game,SIGNAL(finished(int)),this,SLOT(gameFinished()));

	//start
	game->start();
}

void KaminecLauncher::on_action_preference_triggered()
{
	//create preference windows
	auto preference = new Preference(this, activeAuth_);
	preference->show();

	connect(preference,SIGNAL(accepted()),this,SLOT(updateVersionSelect()));
}


void KaminecLauncher::on_gameDir_showPb_clicked()
{
	//ask for game directory
	auto gameDir = QFileDialog::getExistingDirectory(this,"Please choose the game directory.");
	if(gameDir!=""){
		if(gameDir.endsWith("/.minecraft"))
			ui_->gameDir_le->setText(gameDir);
		else
			ui_->gameDir_le->setText(gameDir + "/.minecraft");
	}
	return;
}

void KaminecLauncher::on_moduleSwitch_currentChanged(int index)
{
	//if you click the page of game download,
	//download game version list
	switch (index) {
	case 1:
		gameDownload_->init();
		break;
	default:
		break;
	}
}

void KaminecLauncher::on_download_pb_clicked()
{
	//disable this pushbutton to avoid reclick
	ui_->download_pb->setText("Downloading...");
	ui_->download_pb->setDisabled(true);

	//some settings during download
	ui_->download_treeView->setModel(gameDownload_->getDownloadModel());
	ui_->downloadValue_label->setText(QString("0/%1").arg(gameDownload_->getTotalCount()));
	ui_->downloadProgress_progressBar->setMaximum(gameDownload_->getTotalCount());
	ui_->downloadProgress_progressBar_2->setMaximum(gameDownload_->getTotalCount());

	//signals/slots during download and afer download
	connect(gameDownload_, SIGNAL(downloadedCountChanged(int)),ui_->downloadProgress_progressBar,SLOT(setValue(int)));
	connect(gameDownload_, SIGNAL(downloadedCountChanged(int)),ui_->downloadProgress_progressBar_2,SLOT(setValue(int)));
	connect(gameDownload_, SIGNAL(finished()),this,SLOT(downloadFinished()));
	//start download game
	gameDownload_->download(ui_->versionsList_treeView->currentIndex().row());

}

void KaminecLauncher::loadVersions()
{
	//load exsit versions and check laucher_profiles.json
	QDir dir(Path::versionsPath());
	if(dir.exists())
	{
		dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
		QFileInfoList list = dir.entryInfoList();
		for(auto i : list){
			ui_->version_cb->addItem(i.fileName());
			if(!profileManager_.checkVersion(i.fileName()))
				profileManager_.addVersion(i.fileName(), corePath_);
		}
	}

	//load last used version
	auto index = ui_->version_cb->findText(QSettings().value("lastUsedVersion").toString());
	qDebug()<<QSettings().value("lastUsedVersion").toString();
	if(index != -1)
		ui_->version_cb->setCurrentIndex(index);
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
	ui_->version_cb->clear();
	corePath_ = Path::corePath();
	this->loadVersions();
}

void KaminecLauncher::resizeEvent(QResizeEvent *)
{
	//reset background when resize this window
	setBackGround();
}
