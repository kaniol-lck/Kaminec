#ifndef KAMINECLAUNCHER_H
#define KAMINECLAUNCHER_H

#include <QMainWindow>

#include "profile.h"
#include "savesmanager.h"

namespace Ui {
class KaminecLauncher;
}

class KaminecLauncher : public QMainWindow
{
    Q_OBJECT

public:
    explicit KaminecLauncher(QWidget *parent = 0);
    ~KaminecLauncher();

    const Profile getProfile();
	QPair<QString,QString> getAccount();
    void loadProfileJson();
    void saveProfileJson();
    int download();
private slots:
    void on_fileDlg1_pb_clicked();

    void on_fileDlg2_pb_clicked();

    void on_save_pb_clicked();

    void on_load_pb_clicked();

    void on_start_pb_clicked();

    void on_download_pb_clicked();

    void updateDownloadCount(int);

    void gameFinished();

    void downloadFinished();

    void on_addSaves_pb_clicked();

    void on_deleteSaves_pb_clicked();

	void on_backupSaves_pb_clicked();

	void on_autoJavaPath_pb_clicked();

	void startGame();

	void on_showPassword_pb_clicked();

	void on_verify_cb_stateChanged(int arg1);

private:
    Ui::KaminecLauncher *ui;
	SavesManager savesManager;
    int totalCount;
    QList<QVariant> versionList;
	bool isShowPassword = false;
};

#endif // KAMINECLAUNCHER_H
