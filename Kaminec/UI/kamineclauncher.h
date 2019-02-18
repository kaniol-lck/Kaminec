#ifndef KAMINECLAUNCHER_H
#define KAMINECLAUNCHER_H

#include <QMainWindow>

#include "UI/downloadprogressdialog.h"
#include "UI/kamineclauncher_tabs/startgametab.h"
#include "UI/kamineclauncher_tabs/accounttab.h"
#include "UI/kamineclauncher_tabs/profiletab.h"

namespace Ui {
	class KaminecLauncher;
}

class KaminecLauncher : public QMainWindow
{
    Q_OBJECT

public:
    explicit KaminecLauncher(QWidget *parent = 0);
    ~KaminecLauncher();

	bool startGame();

	void resizeEvent(QResizeEvent *);

private slots:
	void on_action_preferences_triggered();

	void on_action_Download_Progress_triggered();

private:
	void setBackGround();

private:
	Ui::KaminecLauncher *ui_;
	Downloader *downloader_;
	AccountPool *accountPool_;
	ProfileManager *profileManager_;
	Launcher *launcher_;
	DownloadProgressDialog *downloadProgressDialog_;

	StartGameTab *startGameTab_;
	AccountTab *accounttab_;
	ProfileTab *profiletab_;
};

#endif // KAMINECLAUNCHER_H
