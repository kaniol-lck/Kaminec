#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "UI/preferences.h"
#include "assistance/Path.h"
#include "assistance/gamemode.h"

KaminecLauncher::KaminecLauncher(QWidget *parent) :
    QMainWindow(parent),
	ui_(new Ui::KaminecLauncher),
	downloadProgressDialog_(0, &downloader_),
	startGameTab_(new StartGameTab(this, &launcher_, &accountPool_, &profileManager_))
{
	//setup ui
	ui_->setupUi(this);
	ui_->moduleSwitch->addTab(startGameTab_, "&Start Game");
}

KaminecLauncher::~KaminecLauncher()
{
	//delete ui
    delete ui_;
}

void KaminecLauncher::on_action_preferences_triggered()
{
	//create preferences windows
	auto preferences = new Preferences(this, &accountPool_, &profileManager_);
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
	downloadProgressDialog_.show();
}

void KaminecLauncher::resizeEvent(QResizeEvent *)
{
	//reset background when resize this window
	setBackGround();
}
