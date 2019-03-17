#ifndef KAMINECLAUNCHER_H
#define KAMINECLAUNCHER_H

#include <QMainWindow>

class AccountPool;
class ProfileManager;
class Launcher;

class DownloadProgressDialog;
class StartGameTab;
class AccountTab;
class ProfileTab;
class GameOutputTab;

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
