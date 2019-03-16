#ifndef GAMEDOWNLOADDIALOG_H
#define GAMEDOWNLOADDIALOG_H

#include <QDialog>

namespace Ui {
	class GameDownloadDialog;
}

class GameDownload;

class GameDownloadDialog : public QDialog
{
	Q_OBJECT

public:
	explicit GameDownloadDialog(QWidget *parent = nullptr);
	~GameDownloadDialog();

private slots:
	void reapplyFilter();

	void on_download_pb_clicked();

	void on_gameDownload_tableView_pressed(const QModelIndex &);

private:
	Ui::GameDownloadDialog *ui_;
	GameDownload *gameDownload_;
};

#endif // GAMEDOWNLOADDIALOG_H
