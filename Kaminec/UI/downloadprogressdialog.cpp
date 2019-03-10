#include "downloadprogressdialog.h"
#include "ui_downloadprogressdialog.h"

#include "download/Downloader.h"

DownloadProgressDialog::DownloadProgressDialog(QWidget *parent) :
	QDialog(parent),
	ui_(new Ui::DownloadProgressDialog)
{
	Downloader::init(this);
	ui_->setupUi(this);
	ui_->download_treeView->setModel(Downloader::instance()->getModel());
}

DownloadProgressDialog::~DownloadProgressDialog()
{
	delete ui_;
}
