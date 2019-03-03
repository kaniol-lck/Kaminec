#include "downloadprogressdialog.h"
#include "ui_downloadprogressdialog.h"

#include "kits/DownloadKit/DownloadKit.h"

DownloadProgressDialog::DownloadProgressDialog(QWidget *parent) :
	QDialog(parent),
	ui_(new Ui::DownloadProgressDialog)
{
	DownloadKit::init(this);
	ui_->setupUi(this);
	ui_->download_treeView->setModel(DownloadKit::instance()->getModel());
}

DownloadProgressDialog::~DownloadProgressDialog()
{
	delete ui_;
}
