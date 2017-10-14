#ifndef KAMINECLAUNCHER_H
#define KAMINECLAUNCHER_H

#include <QMainWindow>

#include "profile.h"
#include "gamedownload.h"
#include "savesmanager.h"
#include "profilemanager.h"
#include "modsmanager.h"

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

	void getCurrentVersionSelect();

    int download();

	void startGame();

	void resizeEvent(QResizeEvent *);

private slots:

    void on_start_pb_clicked();

    void updateDownloadCount(int);

    void gameFinished();

	void downloadFinished();

    void on_addSaves_pb_clicked();

    void on_deleteSaves_pb_clicked();

	void on_backupSaves_pb_clicked();

	void on_action_preference_triggered();

	void on_gameDir_showPb_clicked();

	void on_moduleSwitch_currentChanged(int index);

	void on_download_pb_clicked();

	void updateVersionSelect();

private:
	void loadVersions();

	void setBackGround();

private:
    Ui::KaminecLauncher *ui;
	SavesManager *savesManager;
	ModsManager *modsManager;
    int totalCount;
	QList<QVariant> versionList;
	GameDownload *gameDownload;
	ProfileManager profileManager;
	QString corePath;
};

#endif // KAMINECLAUNCHER_H
