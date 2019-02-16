#include "startgametab.h"
#include "ui_startgametab.h"

#include <QDebug>

StartGameTab::StartGameTab(QWidget *parent, Launcher *launcher, AccountPool *accountPool, ProfileManager *profileManager) :
	QWidget(parent),
	ui_(new Ui::StartGameTab),
	launcher_(launcher),
	accountPool_(accountPool),
	profileManager_(profileManager)
{
	ui_->setupUi(this);
	connect(launcher, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(stateChanged(QProcess::ProcessState)));
	connect(launcher, SIGNAL(finished(int)), this, SLOT(gameFinished(int)));
}

StartGameTab::~StartGameTab()
{
	delete ui_;
}

void StartGameTab::on_start_pb_clicked()
{
	auto account = accountPool_->check(accountPool_->getSelectedAccountUuid());
	auto profile = profileManager_->getProfile(profileManager_->getSelectedProfileName());

	launcher_->start(profile, account);
}

void StartGameTab::stateChanged(QProcess::ProcessState newState)
{
	qDebug()<<newState;
	if(newState == QProcess::Starting){
		ui_->start_pb->setText("Launching Java...");
		ui_->start_pb->setEnabled(false);
	} else if(newState == QProcess::Running){
		ui_->start_pb->setText("Gaming...");
		ui_->start_pb->setEnabled(false);
	} else /*if(newState == QProcess::NotRunning)*/{
		ui_->start_pb->setText("&Start Game");
		ui_->start_pb->setEnabled(true);
	}
}

void StartGameTab::gameFinished(int i)
{
	qDebug()<<i;
}
