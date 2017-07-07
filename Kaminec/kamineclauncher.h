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
    void loadProfileJson();
    void saveProfileJson();
    int download();
private slots:
    void on_fileDlg1_pb_clicked();

    void on_fileDlg2_pb_clicked();

    void on_save_pb_clicked();

    void on_load_pb_clicked();

    void on_start_pb_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_download_pb_clicked();

    void updateDownloadCount(int);

    void gameFinished();

    void downloadFinished();

    void on_addSaves_pb_clicked();

    void on_deleteSaves_pb_clicked();

    void on_backupSaves_pb_clicked();

private:
    Ui::KaminecLauncher *ui;
    SavesManager SavesManager;
    int totalCount;
};

#endif // KAMINECLAUNCHER_H
