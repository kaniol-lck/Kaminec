#include "profiletab.h"
#include "ui_profiletab.h"

#include "UI/dialogs/profiledialog.h"
#include "LAminec/GameVersionController.h"
#include "LAminec/ProfileManager.h"

ProfileTab::ProfileTab(QWidget *parent, ProfileManager *profileManager) :
	QWidget(parent),
	ui_(new Ui::ProfileTab),
	profileManager_(profileManager)
{
	ui_->setupUi(this);
	ui_->setProfileActive_pb->setEnabled(false);
	ui_->deleteProfile_pb->setEnabled(false);
	ui_->profiles_tableView->setModel(profileManager_->getProfilesModel());

	ui_->profiles_tableView->verticalHeader()->setDefaultSectionSize(40);
	ui_->profiles_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui_->profiles_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui_->profiles_tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
	ui_->profiles_tableView->setColumnWidth(0, 200);
	ui_->profiles_tableView->setColumnWidth(1, 200);
	ui_->profiles_tableView->horizontalHeader()->setSortIndicatorShown(true);
	ui_->profiles_tableView->hideColumn(ProfileManager::Column::Created);
	ui_->profiles_tableView->hideColumn(ProfileManager::Column::LastUsed);

	auto font = ui_->profiles_tableView->horizontalHeader()->font();
	font.setPointSize(13);
	ui_->profiles_tableView->horizontalHeader()->setFont(font);

	connect(ui_->profiles_tableView->horizontalHeader(), &QHeaderView::sectionClicked, profileManager_, &ProfileManager::sortRecord);
	connect(ui_->profiles_tableView->horizontalHeader(), &QHeaderView::sectionClicked, [&]()
	{
		profileManager_->setProfileAscending(ui_->profiles_tableView->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder);
	});
}

ProfileTab::~ProfileTab()
{
	delete ui_;
}

void ProfileTab::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::LanguageChange){
		ui_->retranslateUi(this);
	}else
		QWidget::changeEvent(event);
}

void ProfileTab::on_addProfile_pb_clicked()
{
	auto profileDialog = new ProfileDialog(this, profileManager_);
	profileDialog->exec();
}

void ProfileTab::on_deleteProfile_pb_clicked()
{
	auto index = ui_->profiles_tableView->currentIndex();
	if(index.isValid()){
		profileManager_->removeProfile(profileManager_->nameFromIndex(index));
	}
}

void ProfileTab::on_setProfileActive_pb_clicked()
{
	profileManager_->setSelectedProfileName(profileManager_->nameFromIndex(ui_->profiles_tableView->currentIndex()));

}

void ProfileTab::on_fixProfile_pb_clicked()
{
	profileManager_->fixProfiles(GameVersionController().getGameVersions());
}

void ProfileTab::profileSortRecord()
{
	profileManager_->setProfileAscending(ui_->profiles_tableView->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder);
}

void ProfileTab::on_profiles_tableView_pressed(const QModelIndex &)
{
	ui_->setProfileActive_pb->setEnabled(true);
	ui_->deleteProfile_pb->setEnabled(true);
}

void ProfileTab::on_profiles_tableView_doubleClicked(const QModelIndex &index)
{
	if(index.isValid()){
		auto oldProfileName = profileManager_->nameFromIndex(index);
		if(index.column() == 0){
			profileManager_->setSelectedProfileName(oldProfileName);
		} else{
			auto profileDialog = new ProfileDialog(this, profileManager_, oldProfileName);
			profileDialog->exec();
		}
	}
}
