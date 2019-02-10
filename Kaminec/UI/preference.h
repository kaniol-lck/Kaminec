#ifndef PREFERENCE_H
#define PREFERENCE_H

#include "LAminec/AccountPool.h"
#include "LAminec/ProfileManager.h"
#include "assistance/Custom.h"

#include <QDialog>

namespace Ui {
	class Preference;
}

class Preference : public QDialog
{
	Q_OBJECT

public:
	explicit Preference(QWidget *parent, AccountPool *accountPool, ProfileManager *profileManager);
	~Preference();

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

	void on_gameDir_showPb_clicked();

	void on_check_pb_clicked();

	void on_profiles_cb_currentIndexChanged(const QString &arg1);

	void on_addProfile_pb_clicked();

	void on_editAccount_pb_clicked();

	void on_editProfile_pb_clicked();

	void on_deleteProfile_pb_clicked();

	void on_setActive_pb_clicked();

	void accountSortRecord();

private:
	Ui::Preference *ui_;
	Custom custom_;
	AccountPool *accountPool_;
	ProfileManager *profileManager_;
};

#endif // PREFERENCE_H
