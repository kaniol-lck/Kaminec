#include "preferences.h"
#include "ui_preferences.h"

#include "assistance/Path.h"

#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QEventLoop>

Preferences::Preferences(QWidget *parent, AccountPool *accountPool, ProfileManager *profileManager) :
	QDialog(parent),
	ui_(new Ui::Preferences),
	accountPool_(accountPool),
	profileManager_(profileManager),
	javaTab_(new JavaTab(this)),
	accountTab_(new AccountTab(this, accountPool_)),
	profileTab_(new ProfileTab(this, profileManager_)),
	gameTab_(new GameTab(this)),
	pathTab_(new PathTab(this)),
	lAminecTab_(new LAminecTab(this))
{
	ui_->setupUi(this);
	ui_->preferencesSwitch->addTab(javaTab_, "&Java");
	ui_->preferencesSwitch->addTab(accountTab_, "&Account");
	ui_->preferencesSwitch->addTab(profileTab_, "&Profile");
	ui_->preferencesSwitch->addTab(gameTab_, "&Game");
	ui_->preferencesSwitch->addTab(pathTab_, "&Path");
	ui_->preferencesSwitch->addTab(lAminecTab_, "&LAminec");
}

Preferences::~Preferences()
{
	delete ui_;
}

void Preferences::on_buttonBox_accepted()
{
	javaTab_->accepted();
	gameTab_->accepted();
	pathTab_->accepted();
	lAminecTab_->accepted();

	emit settingfinished();
}
