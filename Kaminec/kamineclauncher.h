#ifndef KAMINECLAUNCHER_H
#define KAMINECLAUNCHER_H

#include <QMainWindow>

#include "profile.h"

namespace Ui {
class KaminecLauncher;
}

class KaminecLauncher : public QMainWindow
{
    Q_OBJECT

public:
    explicit KaminecLauncher(QWidget *parent = 0);
    ~KaminecLauncher();

    const profile getProfile();
private slots:
    void on_fileDlg1_pb_clicked();

    void on_fileDlg2_pb_clicked();

    void on_save_pb_clicked();

    void on_load_pb_clicked();

    void on_start_pb_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::KaminecLauncher *ui;
};

#endif // KAMINECLAUNCHER_H
