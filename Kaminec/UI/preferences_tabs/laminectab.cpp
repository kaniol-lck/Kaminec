#include "laminectab.h"
#include "ui_laminectab.h"

LAminecTab::LAminecTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::LAminecTab)
{
	ui_->setupUi(this);
	ui_->logNumber_spinBox->setValue(custom_.getLogFileNumber());
}

void LAminecTab::accepted()
{
	custom_.setLogFileNumber(ui_->logNumber_spinBox->value());
}

LAminecTab::~LAminecTab()
{
	delete ui_;
}

void LAminecTab::on_logNumber_spinBox_valueChanged(int arg1)
{
	ui_->logTip_label->setVisible(arg1 == -1);
}
