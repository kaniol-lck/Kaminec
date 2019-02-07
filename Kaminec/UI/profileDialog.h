#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include "LAminec/ProfileManager.h"

#include <QDialog>

namespace Ui {
	class ProfileDialog;
}

class ProfileDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ProfileDialog(QWidget *parent, ProfileManager *profilemanager);
	explicit ProfileDialog(QWidget *parent, ProfileManager *profilemanager, const QString &profileName);
	~ProfileDialog();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::ProfileDialog *ui_;
	ProfileManager *profileManager_;
	Profile profile_;

};

#endif // PROFILEDIALOG_H
