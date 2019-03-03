#ifndef DOWNLOADGAMEDIALOG_H
#define DOWNLOADGAMEDIALOG_H

#include <QDialog>

namespace Ui {
	class DownloadGameDialog;
}

class DownloadGameDialog : public QDialog
{
	Q_OBJECT

public:
	explicit DownloadGameDialog(QWidget *parent = nullptr);
	~DownloadGameDialog();

private slots:
	void on_download_pushButton_clicked();

private:
	Ui::DownloadGameDialog *ui;
};

#endif // DOWNLOADGAMEDIALOG_H
