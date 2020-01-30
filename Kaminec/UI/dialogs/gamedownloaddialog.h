#ifndef GAMEDOWNLOADDIALOG_H
#define GAMEDOWNLOADDIALOG_H

#include "assistance/Custom.h"

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

    void on_hideTime_checkBox_stateChanged(int arg1);

    void on_hideUrl_checkBox_stateChanged(int arg1);

    void on_hideReleaseTime_checkBox_stateChanged(int arg1);

    void on_GameDownloadDialog_finished(int);

private:
	Ui::GameDownloadDialog *ui_;
	GameDownload *gameDownload_;
    Custom custom_;
};

#endif // GAMEDOWNLOADDIALOG_H
