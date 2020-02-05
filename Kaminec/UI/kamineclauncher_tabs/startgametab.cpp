#include "startgametab.h"
#include "ui_startgametab.h"

#include "LAminec/AccountPool.h"
#include "LAminec/ProfileManager.h"
#include "launch/Launcher.h"

#include <QMessageBox>
#include <QDebug>
#include <QMenu>

StartGameTab::StartGameTab(QWidget *parent, Launcher *launcher, AccountPool *accountPool, ProfileManager *profileManager) :
	QWidget(parent),
	ui_(new Ui::StartGameTab),
	launcher_(launcher),
	accountPool_(accountPool),
    profileManager_(profileManager),
    menu_(new QMenu(this))
{
    ui_->setupUi(this);

    for(auto profile : profileManager_->getProfiles())
        ui_->profiles_cb->addItem(profile.name());

    ui_->profiles_cb->setCurrentIndex(ui_->profiles_cb->findText(profileManager_->getSelectedProfileName(), Qt::MatchExactly));

    connect(launcher_, &Launcher::stateChanged, [&](QProcess::ProcessState newState)
    {
        qDebug()<<newState;
        if(newState == QProcess::Starting){
            ui_->start_pb->setText(tr("Launching Java..."));
            ui_->start_pb->setEnabled(false);
        } else if(newState == QProcess::Running){
            ui_->start_pb->setText(tr("Gaming..."));
            ui_->start_pb->setEnabled(false);
        } else /*if(newState == QProcess::NotRunning)*/{
            ui_->start_pb->setText(tr("Launch"));
            ui_->start_pb->setEnabled(true);
        }
    });

    connect(launcher_, &Launcher::finished, [&](int /*i*/)
    {
    });

    connect(launcher_, &Launcher::exceptionMessage, [&](QString message)
    {
        QMessageBox::warning(this, tr("error"), message);
    });
}

StartGameTab::~StartGameTab()
{
    delete ui_;
}

void StartGameTab::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange){
        ui_->retranslateUi(this);
    }else
        QWidget::changeEvent(event);
}

void StartGameTab::on_start_pb_clicked()
{
    ui_->start_pb->setText(tr("Preparing..."));
    ui_->start_pb->setEnabled(false);
    auto selectedAccountName = accountPool_->getSelectedAccountName();
    if(!accountPool_->containAccount(selectedAccountName)){
        QMessageBox::warning(this, tr("Launch Error"), tr("Please create your account first."));
        return;
    }
    auto selectedProfileName = profileManager_->getSelectedProfileName();
    if(!profileManager_->containProfile(selectedProfileName)){
        QMessageBox::warning(this, tr("Launch Error"), tr("Please create your profile first."));
        return;
    }
    auto account = accountPool_->check(selectedAccountName);
    auto profile = profileManager_->getProfile(selectedProfileName);

    launcher_->start(profile, account);
}

void StartGameTab::on_profiles_cb_currentIndexChanged(const QString &arg1)
{
    profileManager_->setSelectedProfileName(arg1);
}
