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
	accountTab_(new AccountTab(this, accountPool_)),
	profileTab_(new ProfileTab(this, profileManager_)),
	gameOutputTab_(new GameOutputTab(this, launcher_->getOutputModel()))
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

	ui_->moduleSwitch->addTab(startGameTab_, tr("Start Game"));
	ui_->moduleSwitch->addTab(accountTab_, tr("Account"));
	ui_->moduleSwitch->addTab(profileTab_, tr("Profile"));
	ui_->moduleSwitch->addTab(gameOutputTab_, tr("Game Output"));
//	ui_->moduleSwitch->removeTab(ui_->moduleSwitch->indexOf(gameOutputTab_));

	connect(launcher_, &Launcher::stateChanged, [&](QProcess::ProcessState newState)
	{
		if(newState == QProcess::Starting){
//			ui_->moduleSwitch->addTab(gameOutputTab_, tr("Game Output"));
		} else if(newState == QProcess::NotRunning){
//			ui_->moduleSwitch->removeTab(ui_->moduleSwitch->indexOf(gameOutputTab_));
		}
	});
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
	connect(preferences, &Preferences::updateBackground, this, &setBackGround);
	preferences->exec();
	disconnect(preferences, &Preferences::updateBackground, this, &setBackGround);
}

void KaminecLauncher::setBackGround()
{
	//set backGround
	QPixmap pixmap = QPixmap(Custom().getBackground()).scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
	QPalette palette(this->palette());
	palette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette(palette);
}

void KaminecLauncher::retranslateUi()
{
	ui_->moduleSwitch->setTabText(0, tr("Start Game"));
	ui_->moduleSwitch->setTabText(1, tr("Account"));
	ui_->moduleSwitch->setTabText(2, tr("Profile"));
	ui_->moduleSwitch->setTabText(3, tr("Game Output"));
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

void KaminecLauncher::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::LanguageChange){
		ui_->retranslateUi(this);
		retranslateUi();
	}else
		QMainWindow::changeEvent(event);
}
