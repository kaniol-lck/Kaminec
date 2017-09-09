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
	corePath(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).toString())
{
	//setup ui
	ui->setupUi(this);

	//init ui
	ui->versionsList_treeView->setModel(gameDownload.getVersionsModel());
    ui->downloadProgress_label->setVisible(false);
    ui->downloadProgress_progressBar->setVisible(false);
    ui->downloadProgress_progressBar_2->setVisible(false);
    ui->downloadValue_label->setVisible(false);
	ui->saveMgr_treeView->setModel(savesManager.getModel());

	//load exsit versions
	QDir dir(corePath + "/versions");
	if(dir.exists())
	{
		dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
		QFileInfoList list = dir.entryInfoList();
		for(auto i : list)
			ui->version_cb->addItem(i.fileName());
	}

	//load last used version
	auto index = ui->version_cb->findText(QSettings().value("lastUsedVersion").toString());
	qDebug()<<QSettings().value("lastUsedVersion").toString();
	if(index != -1)
		ui->version_cb->setCurrentIndex(index);

	//load gameDir
	ui->gameDir_le->setText(QSettings().value("gameDir").toString());
}

KaminecLauncher::~KaminecLauncher()
{
	//delete ui
    delete ui;
}

//get current profile
inline const Profile KaminecLauncher::getProfile()
{
	return Profile(QSettings().value("name").toString(),
				   ui->version_cb->currentText(),
				   ui->gameDir_le->text());
}


int KaminecLauncher::download()
{

	auto dm = new DownloadManager(this);
	auto dmp = new DownloadManagerPlus(this);

	ui->download_treeView->setModel(dmp->getModel());
    ui->download_pb->setText("Downloading...");
    ui->download_pb->setDisabled(true);
    ui->downloadProgress_label->setVisible(true);
    ui->downloadProgress_progressBar->setVisible(true);
    ui->downloadProgress_progressBar_2->setVisible(true);
    ui->downloadValue_label->setVisible(true);

	qDebug()<<"???"<<QString("%1/versions/%2/%2.json")
			  .arg(corePath).arg(ui->version_cb->currentText());

    auto fileItem = FileItem(QString("%1.json").arg(ui->version_cb->currentText()),
                             0,
                             QString("NULL"),
							 QString("%1/versions/%2/%2.json")
								 .arg(corePath).arg(ui->version_cb->currentText()),
							 versionList.at(ui->version_cb->currentIndex()).toMap().value("url").toUrl());//!!!!!!!!!!!1
    dm->append(fileItem);
    dm->waitForFinished();

	JsonManager jm(this,ui->version_cb->currentText());

	fileItem = jm.getDownloadClientUrl();
	dmp->append(fileItem);


    auto downloadLibUrls = jm.getDownloadLibUrls();
    for(auto& i:downloadLibUrls){
		i.mPath.prepend(corePath+"/libraries/");
    }

	dmp->append(downloadLibUrls);

	dm->append(jm.getDownloadAssetFileUrl());
	dm->waitForFinished();

	AssetManager assetManager(this,jm.getAssetIndex());
	auto downloadAssetUrls = assetManager.getDownloadAssetUrls();
	dmp->append(downloadAssetUrls);

	qDebug()<<dmp->getTotalCount();

	totalCount = dmp->getTotalCount();
    ui->downloadValue_label->setText(QString("0/%1").arg(totalCount));
	ui->downloadProgress_progressBar->setMaximum(dmp->getTotalCount());
	ui->downloadProgress_progressBar_2->setMaximum(dmp->getTotalCount());

	connect(dmp,SIGNAL(downloadedCountChanged(int)),this,SLOT(updateDownloadCount(int)));
	connect(dmp,SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar,SLOT(setValue(int)));
	connect(dmp,SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar_2,SLOT(setValue(int)));
	connect(dmp,SIGNAL(finished()),this,SLOT(downloadFinished()));
	dmp->waitForFinished();
    return 0;
}


void KaminecLauncher::on_start_pb_clicked()
{
	this->startGame();
}


void KaminecLauncher::updateDownloadCount(int downloaded)
{
    qDebug()<<"changed:"<<downloaded;
	ui->downloadValue_label->setText(QString("%1/%2")
									 .arg(downloaded).arg(totalCount));
}

void KaminecLauncher::downloadFinished()
{
    ui->download_pb->setText("&Download");
    ui->download_pb->setEnabled(true);
    ui->downloadProgress_label->setVisible(false);
    ui->downloadProgress_progressBar->setVisible(false);
    ui->downloadProgress_progressBar_2->setVisible(false);
    ui->downloadValue_label->setVisible(false);
}

void KaminecLauncher::gameFinished()
{
    qDebug()<<"finished";
    ui->start_pb->setText("&Start");
    ui->start_pb->setEnabled(true);
}

void KaminecLauncher::on_addSaves_pb_clicked()
{
	savesManager.addSaves();
}

void KaminecLauncher::on_deleteSaves_pb_clicked()
{
	auto index = ui->saveMgr_treeView->currentIndex();
	savesManager.deleteSaves(index.row());
}

void KaminecLauncher::on_backupSaves_pb_clicked()
{
	savesManager.backup();
}

void KaminecLauncher::startGame()
{
	Game *game;
	if(ui->isVerified_cb->isChecked()){
		game = new Game(this,this->getProfile(),Mode::Online);
	}else{
		game = new Game(this,this->getProfile(),Mode::Offline);
	}
	ui->start_pb->setText("Gaming...");
	ui->start_pb->setDisabled(true);
	connect(game,SIGNAL(finished(int)),this,SLOT(gameFinished()));
	game->start();

}

void KaminecLauncher::on_action_preference_triggered()
{
	auto preference = new Preference(this);
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
	case 2:
		gameDownload.init();
		break;
	default:
		break;
	}
}

void KaminecLauncher::on_download_pb_clicked()
{
	gameDownload.download(ui->versionsList_treeView->currentIndex().row());

	ui->download_treeView->setModel(gameDownload.getVersionsModel());
	ui->downloadValue_label->setText(QString("0/%1").arg(gameDownload.getTotalCount()));
	ui->downloadProgress_progressBar->setMaximum(gameDownload.getTotalCount());
	ui->downloadProgress_progressBar_2->setMaximum(gameDownload.getTotalCount());
	connect(&gameDownload,SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar,SLOT(setValue(int)));
	connect(&gameDownload,SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar_2,SLOT(setValue(int)));
}
