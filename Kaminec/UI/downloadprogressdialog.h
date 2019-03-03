#ifndef DOWNLOADPROGRESSDIALOG_H
#define DOWNLOADPROGRESSDIALOG_H

#include <QDialog>

namespace Ui {
	class DownloadProgressDialog;
}

class DownloadProgressDialog : public QDialog
{
	Q_OBJECT

public:
	explicit DownloadProgressDialog(QWidget *parent = nullptr);
	~DownloadProgressDialog();

private:
	Ui::DownloadProgressDialog *ui_;
};

#endif // DOWNLOADPROGRESSDIALOG_H
