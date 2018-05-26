#ifndef KAMINECLAUNCHER_H
#define KAMINECLAUNCHER_H

#include <QMainWindow>

#include "LAminec/ActiveAuth.h"
#include "LAminec/SavesManager.h"
#include "LAminec/ProfileManager.h"
#include "LAminec/ModsManager.h"
#include "LAminec/LogCleaner.h"
#include "download/Downloader.h"
#include "launch/Launcher.h"
#include "assistance/Custom.h"
#include "check/Checker.h"

namespace Ui {
class KaminecLauncher;
}

class KaminecLauncher : public QMainWindow
{
    Q_OBJECT

public:
    explicit KaminecLauncher(QWidget *parent = 0);
    ~KaminecLauncher();

    void loadProfileJson();

    void saveProfileJson();

	void getCurrentVersionSelect();

    int download();

	void startGame();

	void resizeEvent(QResizeEvent *);

private slots:

    void on_start_pb_clicked();

	void updateDownloadCount(int downloaded);

    void gameFinished();

	void downloadFinished();

    void on_addSaves_pb_clicked();

    void on_deleteSaves_pb_clicked();

	void on_backupSaves_pb_clicked();

	void on_action_preference_triggered();

	void on_gameDir_showPb_clicked();

	void on_moduleSwitch_currentChanged(int index);

	void on_download_pb_clicked();

	void updateProfiles();

	void updateVersions();

	void exceptionMessage(QString message);

	void on_profile_cb_currentIndexChanged(const QString &arg1);

	void on_editProfile_pb_toggled(bool checked);

	void on_addProfile_pb_clicked();

	void on_check_pb_clicked();

private:
	void loadProfiles();

	void loadVersions();

	void loadProfileInfo(const Profile &profile);

	void setBackGround();

private:
	Ui::KaminecLauncher *ui_;
	ActiveAuth activeAuth_;
	SavesManager savesManager_;
	ModsManager modsManager_;
	Downloader gameDownload_;
	ProfileManager profileManager_;
	LogCleaner logCleaner_;
	Launcher launcher_;
	Checker checker_;

	int totalCount_;

	QList<QVariant> versionList_;
	QList<Profile> profileList_;

	Custom custom_;

};

#endif // KAMINECLAUNCHER_H
