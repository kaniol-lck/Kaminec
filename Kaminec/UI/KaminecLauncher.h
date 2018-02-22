#ifndef KAMINECLAUNCHER_H
#define KAMINECLAUNCHER_H

#include <QMainWindow>

#include "messager/profile.h"
#include "LAminec/ActiveAuth.h"
#include "LAminec/savesmanager.h"
#include "LAminec/profilemanager.h"
#include "LAminec/modsmanager.h"
#include "downloader/gamedownload.h"
#include "core/Launcher.h"

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

	void updateVersionSelect();

	void exceptionMessage(QString message);

private:
	void loadVersions();

	void setBackGround();

private:
	Ui::KaminecLauncher *ui_;
	ActiveAuth *activeAuth_;
	SavesManager *savesManager_;
	ModsManager *modsManager_;
	int totalCount_;
	QList<QVariant> versionList_;
	GameDownload *gameDownload_;
	ProfileManager profileManager_;
	QString corePath_;
	Launcher *launcher_;
};

#endif // KAMINECLAUNCHER_H
