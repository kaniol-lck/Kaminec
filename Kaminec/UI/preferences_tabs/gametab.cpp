#include "gametab.h"
#include "ui_gametab.h"

GameTab::GameTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::GameTab)
{
	ui_->setupUi(this);
	ui_->fullScreen_checkBox->setChecked(custom_.getFullScreen());
	ui_->customizeResolution_gb->setChecked(custom_.getCustomizeResolution());
	auto size = custom_.getGameWindowSize();
	ui_->width_sb->setValue(size.first);
	ui_->height_sb->setValue(size.second);
}

void GameTab::accepted()
{
	custom_.setFullScreen(ui_->fullScreen_checkBox->isChecked());
	custom_.setCustomizeResolution(ui_->customizeResolution_gb->isChecked());
	custom_.setGameWindowSize(ui_->width_sb->value(),
							  ui_->height_sb->value());
}

GameTab::~GameTab()
{
	delete ui_;
}

void GameTab::on_fullScreen_checkBox_stateChanged(int arg1)
{
	if(arg1 == Qt::Checked)
		ui_->customizeResolution_gb->setEnabled(false);
	else if(arg1 == Qt::Unchecked)
		ui_->customizeResolution_gb->setEnabled(true);
}
