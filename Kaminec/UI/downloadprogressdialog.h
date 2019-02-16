#ifndef DOWNLOADPROGRESSDIALOG_H
#define DOWNLOADPROGRESSDIALOG_H

#include "download/Downloader.h"

#include <QDialog>

namespace Ui {
	class DownloadProgressDialog;
}

class DownloadProgressDialog : public QDialog
{
	Q_OBJECT

public:
	explicit DownloadProgressDialog(QWidget *parent, Downloader *downloader);
	~DownloadProgressDialog();

private:
	Ui::DownloadProgressDialog *ui_;
	Downloader *downloader_;
};

#endif // DOWNLOADPROGRESSDIALOG_H
