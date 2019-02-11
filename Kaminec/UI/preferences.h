#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "LAminec/AccountPool.h"
#include "LAminec/ProfileManager.h"
#include "assistance/Custom.h"

#include <QDialog>

namespace Ui {
	class Preferences;
}

class Preferences : public QDialog
{
	Q_OBJECT

public:
	explicit Preferences(QWidget *parent, AccountPool *accountPool, ProfileManager *profileManager);
	~Preferences();

private:
	QString getAutoJavaPath();

signals:
	void settingfinished();

private slots:
	void on_corePath_showPb_clicked();

	void on_javaPath_showPb_clicked();

	void on_buttonBox_accepted();

	void on_fullScreen_checkBox_stateChanged(int arg1);

	void on_more_pb_toggled(bool checked);

	void on_javaPath_le_2_textEdited(const QString &arg1);

	void on_javaPath_le_textEdited(const QString &arg1);

	void on_javaPath_showPb_2_clicked();

	void on_versionsPath_showPb_clicked();

	void on_libsPath_showPb_clicked();

	void on_nativesPath_showPb_clicked();

	void on_assetsPath_showPb_clicked();

	void on_indexesPath_showPb_clicked();

	void on_objectsPath_showPb_clicked();

	void on_unusedModsPath_showPb_clicked();

	void on_savesBackupPath_showPb_clicked();

	void on_loggerPath_showPb_clicked();

	void on_logNumber_spinBox_valueChanged(int arg1);

	void on_addAccount_pb_clicked();

	void on_deleteAccount_pb_clicked();

	void on_editAccount_pb_clicked();

	void on_setAccountActive_pb_clicked();

	void on_addProfile_pb_clicked();

	void on_deleteProfile_pb_clicked();

	void on_editProfile_pb_clicked();

	void on_setProfileActive_pb_clicked();

	void accountSortRecord();

	void profileSortRecord();

private:
	Ui::Preferences *ui_;
	Custom custom_;
	AccountPool *accountPool_;
	ProfileManager *profileManager_;
};

#endif // PREFERENCES_H
