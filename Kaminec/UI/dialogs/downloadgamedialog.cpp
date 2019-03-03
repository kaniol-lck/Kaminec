#include "downloadgamedialog.h"
#include "ui_downloadgamedialog.h"

DownloadGameDialog::DownloadGameDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DownloadGameDialog)
{
	ui->setupUi(this);
}

DownloadGameDialog::~DownloadGameDialog()
{
	delete ui;
}

void DownloadGameDialog::on_download_pushButton_clicked()
{

}
