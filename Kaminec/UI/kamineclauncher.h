#ifndef KAMINECLAUNCHER_H
#define KAMINECLAUNCHER_H

#include <QMainWindow>

#include "LAminec/AccountPool.h"
#include "LAminec/ProfileManager.h"
#include "launch/Launcher.h"
#include "UI/downloadprogressdialog.h"

#include "UI/kamineclauncher_tabs/startgametab.h"
#include "UI/kamineclauncher_tabs/accounttab.h"
#include "UI/kamineclauncher_tabs/profiletab.h"
#include "UI/kamineclauncher_tabs/gameoutputtab.h"

namespace Ui {
	class KaminecLauncher;
}

class KaminecLauncher : public QMainWindow
{
    Q_OBJECT

public:
	explicit KaminecLauncher(QWidget *parent = nullptr);
    ~KaminecLauncher();

	bool startGame();

	void resizeEvent(QResizeEvent *);

	void changeEvent(QEvent *event);

private slots:
	void on_action_preferences_triggered();

	void on_action_Download_Progress_triggered();

	void setBackGround();

	void on_actionDownload_Game_triggered();

private:
	void retranslateUi();

private:
	Ui::KaminecLauncher *ui_;
	AccountPool *accountPool_;
	ProfileManager *profileManager_;
	Launcher *launcher_;
	DownloadProgressDialog *downloadProgressDialog_;

	StartGameTab *startGameTab_;
	AccountTab *accountTab_;
	ProfileTab *profileTab_;
	GameOutputTab *gameOutputTab_;
};

#endif // KAMINECLAUNCHER_H
