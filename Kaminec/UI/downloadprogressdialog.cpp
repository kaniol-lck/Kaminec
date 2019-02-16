#include "downloadprogressdialog.h"
#include "ui_downloadprogressdialog.h"

DownloadProgressDialog::DownloadProgressDialog(QWidget *parent, Downloader *downloader) :
	QDialog(parent),
	ui_(new Ui::DownloadProgressDialog),
	downloader_(downloader)
{
	ui_->setupUi(this);
	ui_->download_tableView->setModel(downloader_->getDownloadModel());
}

DownloadProgressDialog::~DownloadProgressDialog()
{
	delete ui_;
}
