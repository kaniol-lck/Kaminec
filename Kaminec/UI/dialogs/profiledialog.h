#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include "messenger/Profile.h"

#include <QDialog>
#include <memory>

namespace Ui {
	class ProfileDialog;
}

class ProfileManager;

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
	std::shared_ptr<Profile> oldProfile_;

};

#endif // PROFILEDIALOG_H
