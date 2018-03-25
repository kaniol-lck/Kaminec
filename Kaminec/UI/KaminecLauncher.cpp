#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "UI/Preference.h"
#include "core/Path.h"
#include "core/gamemode.h"

#include <QDebug>
#include <QString>
#include <QDir>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>

KaminecLauncher::KaminecLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::KaminecLauncher),
	activeAuth_(new ActiveAuth(this)),
	savesManager_(new SavesManager(this)),
	modsManager_(new ModsManager(this)),
	gameDownload_(new GameDownload(this)),
	launcher_(new Launcher(this))
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

	ui_->profileName_label->setVisible(false);
	ui_->profileName_le->setVisible(false);
	ui_->version_label->setVisible(false);
	ui_->version_cb->setVisible(false);
	ui_->gameDir_label->setVisible(false);
	ui_->gameDir_le->setVisible(false);
	ui_->gameDir_showPb->setVisible(false);

	loadVersions();
	loadProfiles();

	ui_->isVerified_cb->setChecked(custom_.getOnlineMode());

	modsManager_->setGameDir(ui_->gameDir_le->text());
	ui_->versionsList_treeView->setModel(gameDownload_->getVersionsModel());

	connect(launcher_,SIGNAL(finished(int)),this,SLOT(gameFinished()));
	connect(launcher_,SIGNAL(exceptionMessage(QString)),this,SLOT(exceptionMessage(QString)));
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

	//update versions
	updateVersions();
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
	custom_.setOnlineMode(auth.getAuthMode() == Mode::Online);

	auto profile = profileManager_.getSelectedProfile();

	//prepare mods
	modsManager_->start();

	//ui during gaming
	ui_->start_pb->setText("Gaming...");
	ui_->start_pb->setDisabled(true);

	//start
	launcher_->start(profile, auth);

}

void KaminecLauncher::on_action_preference_triggered()
{
	//create preference windows
	auto preference = new Preference(this, activeAuth_);
	preference->show();

	connect(preference,SIGNAL(settingfinished()),this,SLOT(updateProfiles()));
	connect(preference,SIGNAL(settingfinished()),this,SLOT(updateVersions()));
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

void KaminecLauncher::updateProfiles()
{
	ui_->profile_cb->clear();
	profileManager_.refresh();
	loadProfiles();
}

void KaminecLauncher::loadProfiles()
{
	//get selected profile
	auto selectedProfile = profileManager_.getSelectedProfile();

	//get profile list from profileManager
	profileList_ = profileManager_.getProfileList();

	//show profile
	for(const auto& profile : profileList_)
		if(profile.name_ != "") //distinguish it by profile type in another day
			ui_->profile_cb->addItem(profile.name_);

	//load selected profile info
	loadProfileInfo(selectedProfile);

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
			versionList_.append(i.fileName());
			ui_->version_cb->addItem(i.fileName());
			if(!profileManager_.checkVersion(i.fileName()))
				profileManager_.addVersion(i.fileName(), Path::corePath());
		}
	}
}

void KaminecLauncher::loadProfileInfo(const Profile &profile)
{
	//profile name
	auto index = ui_->profile_cb->findText(profile.name_);
	if(index != -1) {
		ui_->profile_cb->setCurrentIndex(index);
		ui_->profileName_le->setText(profile.name_);
	}

	//version
	index = ui_->version_cb->findText(profile.lastVersionId_);
	if(index != -1) ui_->version_cb->setCurrentIndex(index);
	else ui_->statusBar->showMessage(QString("version not exist:") + profile.name_, 3000);

	//game directory
	ui_->gameDir_le->setText(profile.gameDir_);
}

void KaminecLauncher::setBackGround()
{
	//set backGround
	QPixmap pixmap = QPixmap(":/main/res/background.png").scaled(this->size());
	QPalette palette(this->palette());
	palette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette(palette);
}

void KaminecLauncher::updateVersions()
{
	ui_->version_cb->clear();
	versionList_.clear();
	loadVersions();
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

void KaminecLauncher::on_profile_cb_currentIndexChanged(const QString &arg1)
{
	for(const auto& profile : profileList_)
		if(profile.name_ == arg1){
			loadProfileInfo(profile);
			profileManager_.setSelectedProfile(arg1);
		}
}

void KaminecLauncher::on_editProfile_pb_toggled(bool checked)
{
	//Accept
	ui_->profile_cb->setEnabled(!checked);
	if(!checked){
		auto newName = ui_->profileName_le->text();
		if(newName == "") return;

		auto profile = profileManager_.getSelectedProfile();
		profile.name_ = newName;
		profile.lastVersionId_ = ui_->version_cb->currentText();
		profile.gameDir_ = ui_->gameDir_le->text();

		profileManager_.removeProfile(ui_->profile_cb->currentText());
		profileManager_.insertProfile(profile);
		profileManager_.setSelectedProfile(newName);
		updateProfiles();
	}

	ui_->profileName_label->setVisible(checked);
	ui_->profileName_le->setVisible(checked);
	ui_->version_label->setVisible(checked);
	ui_->version_cb->setVisible(checked);
	ui_->gameDir_label->setVisible(checked);
	ui_->gameDir_le->setVisible(checked);
	ui_->gameDir_showPb->setVisible(checked);

	ui_->editProfile_pb->setText(checked?"&OK":"&Edit");
}
