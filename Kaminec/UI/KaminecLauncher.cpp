#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "UI/preferences.h"
#include "assistance/Path.h"
#include "assistance/gamemode.h"

#include <QGraphicsEffect>

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

	auto *shadowEffect = new QGraphicsDropShadowEffect();
	shadowEffect->setBlurRadius(4);
	shadowEffect->setColor(QColor(0, 0, 0, 160));
	shadowEffect->setOffset(2);
	ui_->moduleSwitch->setGraphicsEffect(shadowEffect);

	auto *shadowEffect2 = new QGraphicsDropShadowEffect();
	shadowEffect2->setBlurRadius(4);
	shadowEffect2->setColor(QColor(0, 0, 0, 160));
	shadowEffect2->setOffset(2);
	ui_->mainToolBar->setGraphicsEffect(shadowEffect2);

	ui_->moduleSwitch->addTab(startGameTab_, tr("&Start Game"));
	ui_->moduleSwitch->addTab(accounttab_, tr("&Account"));
	ui_->moduleSwitch->addTab(profiletab_, tr("&Profile"));
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
