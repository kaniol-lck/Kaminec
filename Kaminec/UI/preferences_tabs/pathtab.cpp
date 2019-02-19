#include "pathtab.h"
#include "ui_pathtab.h"

#include <QFileDialog>

PathTab::PathTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::PathTab)
{
	ui_->setupUi(this);
	ui_->versionsPath_label->setVisible(false);
	ui_->versionsPath_le->setVisible(false);
	ui_->versionsPath_showPb->setVisible(false);
	ui_->libsPath_label->setVisible(false);
	ui_->libsPath_le->setVisible(false);
	ui_->libsPath_showPb->setVisible(false);
	ui_->nativesPath_label->setVisible(false);
	ui_->nativesPath_le->setVisible(false);
	ui_->nativesPath_showPb->setVisible(false);
	ui_->assetsPath_label->setVisible(false);
	ui_->assetsPath_le->setVisible(false);
	ui_->assetsPath_showPb->setVisible(false);
	ui_->indexesPath_label->setVisible(false);
	ui_->indexesPath_le->setVisible(false);
	ui_->indexesPath_showPb->setVisible(false);
	ui_->objectsPath_label->setVisible(false);
	ui_->objectsPath_le->setVisible(false);
	ui_->objectsPath_showPb->setVisible(false);
	ui_->customPathHelper_tb->setVisible(false);

	ui_->corePath_le->setText(custom_.getCoreGameFileDirectory());
	ui_->defaultGamePath_le->setText(custom_.getDefaultGameDirectory());
	ui_->versionsPath_le->setText(custom_.getGameVersionsDirectory());
	ui_->libsPath_le->setText(custom_.getGameLibrariesDirectory());
	ui_->nativesPath_le->setText(custom_.getGameNativesDirectory());
	ui_->assetsPath_le->setText(custom_.getAssetsDirectory());
	ui_->indexesPath_le->setText(custom_.getAssetsIndexesDirectory());
	ui_->objectsPath_le->setText(custom_.getAssetsObjectsDirectory());
	ui_->unusedModsPath_le->setText(custom_.getUnusedModsDirectory());
	ui_->savesBackupPath_le->setText(custom_.getSavesBackupDirectory());
	ui_->loggerPath_le->setText(custom_.getLoggerDirectory());
	ui_->javaPath_le_2->setText(custom_.getJavaDirectory());
}

void PathTab::accepted()
{
	custom_.setCoreGameFileDirectory(ui_->corePath_le->text());
	custom_.setDefaultGameDirectory(ui_->defaultGamePath_le->text());
	custom_.setGameVersionsDirectory(ui_->versionsPath_le->text());
	custom_.setGameLibrariesDirectory(ui_->libsPath_le->text());
	custom_.setGameNativesDirectory(ui_->nativesPath_le->text());
	custom_.setAssetsDirectory(ui_->assetsPath_le->text());
	custom_.setAssetsIndexesDirectory(ui_->indexesPath_le->text());
	custom_.setAssetsObjectsDirectory(ui_->objectsPath_le->text());
	custom_.setUnusedModsDirectory(ui_->unusedModsPath_le->text());
	custom_.setSavesBackupDirectory(ui_->savesBackupPath_le->text());
	custom_.setLoggerDirectory(ui_->loggerPath_le->text());
}

PathTab::~PathTab()
{
	delete ui_;
}

void PathTab::on_javaPath_showPb_2_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the version directory"),
												  ui_->versionsPath_le->text());

	if(path!="")
		ui_->versionsPath_le->setText(path);
}

void PathTab::on_corePath_showPb_clicked()
{
	auto corePath = QFileDialog::getExistingDirectory(0, tr("Please choose the upper directory,we will automaticly create \".minecraft\" folder"),
													  ui_->corePath_le->text());
	if(corePath!=""){
		if(corePath.endsWith("/.minecraft"))
			ui_->corePath_le->setText(corePath);
		else
			ui_->corePath_le->setText(corePath + "/.minecraft");
	}

}

void PathTab::on_defaultGamePath_showPb_clicked()
{
	auto defaultGamePath = QFileDialog::getExistingDirectory(0, tr("Please choose the upper directory,we will automaticly create \".minecraft\" folder"),
													  ui_->defaultGamePath_le->text());
	if(defaultGamePath!=""){
		if(defaultGamePath.endsWith("/.minecraft"))
			ui_->defaultGamePath_le->setText(defaultGamePath);
		else
			ui_->defaultGamePath_le->setText(defaultGamePath + "/.minecraft");
	}
}

void PathTab::on_versionsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the version directory"),
												  ui_->versionsPath_le->text());

	if(path!="")
		ui_->versionsPath_le->setText(path);
}

void PathTab::on_libsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the libraries directory"),
												  ui_->libsPath_le->text());

	if(path!="")
		ui_->libsPath_le->setText(path);
}

void PathTab::on_nativesPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the natives directory"),
												  ui_->nativesPath_le->text());

	if(path!="")
		ui_->nativesPath_le->setText(path);
}

void PathTab::on_assetsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the assets directory"),
												  ui_->assetsPath_le->text());

	if(path!="")
		ui_->assetsPath_le->setText(path);
}

void PathTab::on_indexesPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the asset indexes directory"),
												  ui_->indexesPath_le->text());

	if(path!="")
		ui_->indexesPath_le->setText(path);
}

void PathTab::on_objectsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the asset objects directory"),
												  ui_->objectsPath_le->text());

	if(path!="")
		ui_->objectsPath_le->setText(path);
}

void PathTab::on_unusedModsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the unused mods directory"),
												  ui_->unusedModsPath_le->text());

	if(path!="")
		ui_->unusedModsPath_le->setText(path);
}

void PathTab::on_savesBackupPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the saves backup directory"),
												  ui_->savesBackupPath_le->text());

	if(path!="")
		ui_->savesBackupPath_le->setText(path);
}

void PathTab::on_loggerPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Please choose the logger directory"),
												  ui_->loggerPath_le->text());

	if(path!="")
		ui_->loggerPath_le->setText(path);
}

void PathTab::on_more_pb_toggled(bool checked)
{
	ui_->versionsPath_label->setVisible(checked);
	ui_->versionsPath_le->setVisible(checked);
	ui_->versionsPath_showPb->setVisible(checked);
	ui_->libsPath_label->setVisible(checked);
	ui_->libsPath_le->setVisible(checked);
	ui_->libsPath_showPb->setVisible(checked);
	ui_->nativesPath_label->setVisible(checked);
	ui_->nativesPath_le->setVisible(checked);
	ui_->nativesPath_showPb->setVisible(checked);
	ui_->assetsPath_label->setVisible(checked);
	ui_->assetsPath_le->setVisible(checked);
	ui_->assetsPath_showPb->setVisible(checked);
	ui_->indexesPath_label->setVisible(checked);
	ui_->indexesPath_le->setVisible(checked);
	ui_->indexesPath_showPb->setVisible(checked);
	ui_->objectsPath_label->setVisible(checked);
	ui_->objectsPath_le->setVisible(checked);
	ui_->objectsPath_showPb->setVisible(checked);
	ui_->customPathHelper_tb->setVisible(checked);

	ui_->more_pb->setText(checked?tr("Fold"):tr("More"));
}
