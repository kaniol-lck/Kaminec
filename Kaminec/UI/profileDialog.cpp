#include "profileDialog.h"
#include "ui_profileDialog.h"

#include "LAminec/GameVersionController.h"

#include <QMessageBox>

ProfileDialog::ProfileDialog(QWidget *parent, ProfileManager *profilemanager) :
	QDialog(parent),
	ui_(new Ui::ProfileDialog),
	profileManager_(profilemanager)
{
	ui_->setupUi(this);
	ui_->hint_label->setText("Create Profile");
	setWindowTitle("Create Profile");
	setFixedSize(360, 200);
	for(auto version : GameVersionController().getAllVersions()){
		ui_->version_cb->addItem(version.versionName());
	}
}

ProfileDialog::ProfileDialog(QWidget *parent, ProfileManager *profilemanager, const QString &profileName) :
	ProfileDialog(parent, profilemanager)
{
	oldProfile_ =  std::make_shared<Profile>(profileManager_->getProfile(profileName));
	ui_->hint_label->setText("Edit Profile");
	setWindowTitle("Edit Profile");
	ui_->profileName_le->setText(oldProfile_->name());
	ui_->gameDir_le->setText(oldProfile_->gameDir());
	ui_->version_cb->setCurrentIndex(ui_->version_cb->findText(oldProfile_->lastVersionId(), Qt::MatchExactly));
}

ProfileDialog::~ProfileDialog()
{
	delete ui_;
}

void ProfileDialog::on_buttonBox_accepted()
{
	auto name = ui_->profileName_le->text();
	auto version = ui_->version_cb->currentText();
	auto gameDir = ui_->gameDir_le->text();

	Profile profile(name, version, gameDir);

	if(name.isEmpty()){
		QMessageBox::warning(this, "Warning", "The profile name cannot be empty.");
		return;
	}
	if(gameDir.isEmpty()){
		QMessageBox::warning(this, "Warning", "The game directory cannot be empty.");
		return;
	}
	if(profileManager_->containProfile(profile.name())){
		QMessageBox::warning(this, "Warning", "The profile already exists.");
		return;
	}

	if(oldProfile_){
		profileManager_->removeProfile(oldProfile_->name());
		profileManager_->insertProfile(profile);
		profileManager_->setSelectedProfileName(profile.name());
	} else{
		if(profileManager_->containProfile(profile.name())){
			QMessageBox::warning(this, "Warning", "The profile already exists.");
			return;
		}
		profileManager_->insertProfile(profile);
	}
	accept();
	return;
}
