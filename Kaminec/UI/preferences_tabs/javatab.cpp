#include "javatab.h"
#include "ui_javatab.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>

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
    ui_->customJVMArgs_gb->setChecked(custom_.getUseCustomJVMArguments());
    for(const auto& arg : custom_.getCustomJVMArguments())
        ui_->customJVMArgs_listWidget->addItem(arg);
}

void JavaTab::accepted()
{
	custom_.setJavaDirectory(ui_->javaPath_le->text());
	custom_.setMemoryAllocateRange(ui_->minMem_sb->value(),
								   ui_->maxMem_sb->value());
    custom_.setUseCustomJVMArguments(ui_->customJVMArgs_gb->isChecked());
    QStringList args;
    for(auto i= 0; i < ui_->customJVMArgs_listWidget->count(); ++i){
        args << ui_->customJVMArgs_listWidget->item(i)->text();
    }
    custom_.setCustomJVMArguments(args);
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

void JavaTab::on_addArg_pushButton_clicked()
{
    auto arg = QInputDialog::getText(this, tr("custom Argument."), tr("Input your custom Argument here:"));
    if(!arg.isNull() && arg != "")
        ui_->customJVMArgs_listWidget->addItem(arg);
}

void JavaTab::on_removeArg_pushButton_clicked()
{
    for(const auto& item : ui_->customJVMArgs_listWidget->selectedItems()){
        delete item;
    }
}
