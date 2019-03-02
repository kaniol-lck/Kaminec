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
	gameTab_(new GameTab(this)),
	pathTab_(new PathTab(this)),
	launcherTab_(new LauncherTab(this)),
	themeTab_(new ThemeTab(this))
{
	ui_->setupUi(this);
	ui_->preferencesSwitch->addTab(javaTab_, tr("Java"));
	ui_->preferencesSwitch->addTab(gameTab_, tr("Game"));
	ui_->preferencesSwitch->addTab(pathTab_, tr("Path"));
	ui_->preferencesSwitch->addTab(launcherTab_, tr("Launcher"));
	ui_->preferencesSwitch->addTab(themeTab_, tr("Theme"));

	connect(themeTab_, &ThemeTab::updateBackground, this, &updateBackground);
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
	launcherTab_->accepted();
	themeTab_->accepted();

	emit settingfinished();
}
