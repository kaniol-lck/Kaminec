#include "gameoutputtab.h"
#include "ui_gameoutputtab.h"

GameOutputTab::GameOutputTab(QWidget *parent, QStandardItemModel *model) :
	QWidget(parent),
	ui_(new Ui::GameOutputTab)
{
	ui_->setupUi(this);
	ui_->output_listView->setModel(model);
}

GameOutputTab::~GameOutputTab()
{
	delete ui_;
}
