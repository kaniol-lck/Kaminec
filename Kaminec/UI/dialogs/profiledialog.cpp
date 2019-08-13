#include "profiledialog.h"
#include "ui_profiledialog.h"

#include "LAminec/ProfileManager.h"
#include "LAminec/GameVersionController.h"

#include <QMessageBox>

ProfileDialog::ProfileDialog(QWidget *parent, ProfileManager *profilemanager) :
	QDialog(parent),
	ui_(new Ui::ProfileDialog),
	profileManager_(profilemanager)
{
	ui_->setupUi(this);
	ui_->hint_label->setText(tr("Create Profile"));
	setWindowTitle(tr("Create Profile"));
	setFixedSize(360, 185);
	for(const auto &version : GameVersionController().getGameVersions())
		ui_->version_cb->addItem(version.versionName());
}

ProfileDialog::ProfileDialog(QWidget *parent, ProfileManager *profilemanager, const QString &profileName) :
	ProfileDialog(parent, profilemanager)
{
	oldProfile_ =  std::make_shared<Profile>(profileManager_->getProfile(profileName));
	ui_->hint_label->setText(tr("Edit Profile"));
	setWindowTitle(tr("Edit Profile"));
	ui_->profileName_le->setText(oldProfile_->name());
	ui_->gameDir_le->setText(oldProfile_->gameDir());
	ui_->version_cb->setCurrentIndex(ui_->version_cb->findText(oldProfile_->lastVersionId().versionName(), Qt::MatchExactly));
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

	Profile profile(name, ProfileType::Custom, GameVersion(version), gameDir, QDateTime::currentDateTime());

	if(name.isEmpty()){
		QMessageBox::warning(this, tr("Warning"), tr("The profile name cannot be empty."));
		return;
	}
	if(gameDir.isEmpty()){
		QMessageBox::warning(this, tr("Warning"), tr("The game directory cannot be empty."));
		return;
	}

	if(oldProfile_){
		profileManager_->editProfile(oldProfile_->name(), profile);
	} else{
		if(profileManager_->containProfile(profile.name())){
			QMessageBox::warning(this, tr("Warning"), tr("The profile already exists."));
			return;
		}
		profileManager_->insertProfile(profile);
	}
	accept();
	return;
}
