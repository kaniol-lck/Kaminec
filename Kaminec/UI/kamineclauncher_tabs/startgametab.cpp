#include "startgametab.h"
#include "ui_startgametab.h"

#include <QMessageBox>
#include <QDebug>

StartGameTab::StartGameTab(QWidget *parent, Launcher *launcher, AccountPool *accountPool, ProfileManager *profileManager) :
	QWidget(parent),
	ui_(new Ui::StartGameTab),
	launcher_(launcher),
	accountPool_(accountPool),
	profileManager_(profileManager)
{
	ui_->setupUi(this);
	connect(launcher_, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(stateChanged(QProcess::ProcessState)));
	connect(launcher_, SIGNAL(finished(int)), this, SLOT(gameFinished(int)));
	connect(launcher_, SIGNAL(exceptionMessage(QString)), this, SLOT(exceptionMessage(QString)));
}

StartGameTab::~StartGameTab()
{
	delete ui_;
}

void StartGameTab::on_start_pb_clicked()
{
	auto selectedAccountUuid = accountPool_->getSelectedAccountUuid();
	if(!accountPool_->containAccount(selectedAccountUuid)){
		QMessageBox::warning(this, "Launch Error", "Please create your account first.");
		return;
	}
	auto selectedProfileName = profileManager_->getSelectedProfileName();
	if(!profileManager_->containProfile(selectedProfileName)){
		QMessageBox::warning(this, "Launch Error", "Please create your profile first.");
		return;
	}
	auto account = accountPool_->check(selectedAccountUuid);
	auto profile = profileManager_->getProfile(selectedProfileName);

	launcher_->start(profile, account);
	ui_->start_pb->setText("Gaming...");
	ui_->start_pb->setEnabled(false);
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
		ui_->start_pb->setText("&Launch");
		ui_->start_pb->setEnabled(true);
	}
}

void StartGameTab::gameFinished(int /*i*/)
{
	ui_->start_pb->setText("&Launch");
	ui_->start_pb->setEnabled(true);
}

void StartGameTab::exceptionMessage(QString message)
{
	QMessageBox::warning(this, "error", message);
}
