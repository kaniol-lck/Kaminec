#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "UI/preferences.h"
#include "assistance/Path.h"
#include "assistance/gamemode.h"

KaminecLauncher::KaminecLauncher(QWidget *parent) :
    QMainWindow(parent),
	ui_(new Ui::KaminecLauncher),
	downloader_(new Downloader(this)),
	accountPool_(new AccountPool(this)),
	profileManager_(new ProfileManager(this)),
	launcher_(new Launcher(this)),
	downloadProgressDialog_(new DownloadProgressDialog(this, downloader_)),
	startGameTab_(new StartGameTab(this, launcher_, accountPool_, profileManager_)),
	accounttab_(new AccountTab(this, accountPool_)),
	profiletab_(new ProfileTab(this, profileManager_))
{
	//setup ui
	ui_->setupUi(this);
	setFixedSize(960,540);
	ui_->moduleSwitch->addTab(startGameTab_, "&Start Game");
	ui_->moduleSwitch->addTab(accounttab_, "&Account");
	ui_->moduleSwitch->addTab(profiletab_, "&Profile");
}

KaminecLauncher::~KaminecLauncher()
{
	//delete ui
    delete ui_;
}

void KaminecLauncher::on_action_preferences_triggered()
{
	//create preferences windows
	auto preferences = new Preferences(this, accountPool_, profileManager_);
	preferences->show();
}

void KaminecLauncher::setBackGround()
{
	//set backGround
	QPixmap pixmap = QPixmap(":/main/res/background.png").scaled(this->size());
	QPalette palette(this->palette());
	palette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette(palette);
}

void KaminecLauncher::on_action_Download_Progress_triggered()
{
	downloadProgressDialog_->show();
}

void KaminecLauncher::resizeEvent(QResizeEvent *)
{
	//reset background when resize this window
	setBackGround();
}
