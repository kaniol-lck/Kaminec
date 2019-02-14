#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "UI/preferences.h"
#include "assistance/Path.h"
#include "assistance/gamemode.h"

#include <QDebug>
#include <QString>
#include <QDir>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>

KaminecLauncher::KaminecLauncher(QWidget *parent) :
    QMainWindow(parent),
	ui_(new Ui::KaminecLauncher)
{
	//setup ui
	ui_->setupUi(this);

	//init ui
	ui_->modsMgr_treeView->setModel(modsManager_.getModel());
    ui_->downloadProgress_label->setVisible(false);
    ui_->downloadProgress_progressBar->setVisible(false);
    ui_->downloadProgress_progressBar_2->setVisible(false);
    ui_->downloadValue_label->setVisible(false);
	ui_->saveMgr_treeView->setModel(savesManager_.getModel());

	ui_->versionsList_treeView->setModel(gameDownload_.getVersionsModel());

	logCleaner_.clean();

	connect(&launcher_, SIGNAL(finished(int)), this, SLOT(gameFinished()));
	connect(&launcher_, SIGNAL(exceptionMessage(QString)), this, SLOT(exceptionMessage(QString)));
}

KaminecLauncher::~KaminecLauncher()
{
	//delete ui
    delete ui_;
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

	//!!!!!!
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
	savesManager_.addSaves();
}

void KaminecLauncher::on_deleteSaves_pb_clicked()
{
	//delete saves
	auto index = ui_->saveMgr_treeView->currentIndex();
	savesManager_.deleteSaves(index.row());
}

void KaminecLauncher::on_backupSaves_pb_clicked()
{
	//backup saves
	savesManager_.backup();
}

bool KaminecLauncher::startGame()
{
	//check Auth for game
	auto account = accountPool_.check(accountPool_.getSelectedAccountUuid());

	auto profile = profileManager_.getProfile(profileManager_.getSelectedProfileName());

	//prepare mods
	modsManager_.start();

	//ui during gaming
	ui_->start_pb->setText("Gaming...");
	ui_->start_pb->setDisabled(true);

	//start
	launcher_.start(profile, account);

	return true;
}

void KaminecLauncher::on_action_preferences_triggered()
{
	//create preferences windows
	auto preferences = new Preferences(this, &accountPool_, &profileManager_);
	preferences->show();
}

void KaminecLauncher::on_moduleSwitch_currentChanged(int index)
{
	//if you click the page of game download,
	//download game version list
	switch (index) {
	case 1:
		gameDownload_.init();
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
	ui_->download_treeView->setModel(gameDownload_.getDownloadModel());
	ui_->downloadValue_label->setText(QString("0/%1").arg(gameDownload_.getTotalCount()));
	ui_->downloadProgress_progressBar->setMaximum(gameDownload_.getTotalCount());
	ui_->downloadProgress_progressBar_2->setMaximum(gameDownload_.getTotalCount());

	//signals/slots during download and afer download
	connect(&gameDownload_, SIGNAL(downloadedCountChanged(int)),ui_->downloadProgress_progressBar,SLOT(setValue(int)));
	connect(&gameDownload_, SIGNAL(downloadedCountChanged(int)),ui_->downloadProgress_progressBar_2,SLOT(setValue(int)));
	connect(&gameDownload_, SIGNAL(finished()),this,SLOT(downloadFinished()));
	//start download game
	gameDownload_.download(ui_->versionsList_treeView->currentIndex().row());

}

void KaminecLauncher::setBackGround()
{
	//set backGround
	QPixmap pixmap = QPixmap(":/main/res/background.png").scaled(this->size());
	QPalette palette(this->palette());
	palette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette(palette);
}

void KaminecLauncher::exceptionMessage(QString message)
{
	gameFinished();
	QMessageBox::warning(this,"Error" , message);
}

void KaminecLauncher::resizeEvent(QResizeEvent *)
{
	//reset background when resize this window
	setBackGround();
}
