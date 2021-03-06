#ifndef PROFILETAB_H
#define PROFILETAB_H

#include <QWidget>

namespace Ui {
	class ProfileTab;
}

class ProfileManager;

class ProfileTab : public QWidget
{
	Q_OBJECT

public:
	explicit ProfileTab(QWidget *parent, ProfileManager *profileManager);
	~ProfileTab();

	void changeEvent(QEvent *event);

private slots:
	void on_addProfile_pb_clicked();

	void on_deleteProfile_pb_clicked();

	void on_setProfileActive_pb_clicked();

	void on_fixProfile_pb_clicked();

	void profileSortRecord();

	void on_profiles_tableView_pressed(const QModelIndex &);

	void on_profiles_tableView_doubleClicked(const QModelIndex &index);

private:
	Ui::ProfileTab *ui_;
	ProfileManager *profileManager_;
};

#endif // PROFILETAB_H
