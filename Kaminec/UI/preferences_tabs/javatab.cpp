#include "javatab.h"
#include "ui_javatab.h"

#include <QFileDialog>

JavaTab::JavaTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::JavaTab)
{
	ui_->setupUi(this);

	ui_->javaPath_le->setText(custom_.getJavaDirectory());
	auto range = custom_.getMemoryAllocateRange();
	ui_->minMem_sb->setValue(range.first);
	ui_->maxMem_sb->setValue(range.second);
	ui_->javaPath_le->setText(custom_.getJavaDirectory());

}

void JavaTab::accepted()
{
	custom_.setJavaDirectory(ui_->javaPath_le->text());
	custom_.setMemoryAllocateRange(ui_->minMem_sb->value(),
								   ui_->maxMem_sb->value());
}

JavaTab::~JavaTab()
{
	delete ui_;
}

void JavaTab::on_javaPath_showPb_clicked()
{
	auto javaPath = QFileDialog::getOpenFileName(this,
												 tr("Choose javaw,exe..."),
												 "C:/","javaw(javaw.exe)");
	if(javaPath!="")
		ui_->javaPath_le->setText(javaPath);
}
