#include "gametab.h"
#include "ui_gametab.h"

GameTab::GameTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::GameTab)
{
	ui_->setupUi(this);
	ui_->fullScreen_checkBox->setChecked(custom_.getGameWindowFullScreen());
	auto size = custom_.getGameWindowSize();
	ui_->width_sb->setValue(size.first);
	ui_->height_sb->setValue(size.second);
}

void GameTab::accepted()
{
	custom_.setGameWindowFullScreen(ui_->fullScreen_checkBox->isChecked());
	custom_.setGameWindowSize(ui_->width_sb->value(),
							  ui_->height_sb->value());
}

GameTab::~GameTab()
{
	delete ui_;
}

void GameTab::on_fullScreen_checkBox_stateChanged(int arg1)
{
	if(arg1 == Qt::Checked){
		ui_->width_sb->setEnabled(false);
		ui_->height_sb->setEnabled(false);
	} else /*arg1 == Qt::Unchecked*/{
		ui_->width_sb->setEnabled(true);
		ui_->height_sb->setEnabled(true);
	}
}
