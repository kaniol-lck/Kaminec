#ifndef STARTGAMETAB_H
#define STARTGAMETAB_H

#include <QWidget>

namespace Ui {
	class StartGameTab;
}

class AccountPool;
class ProfileManager;
class Launcher;

class StartGameTab : public QWidget
{
	Q_OBJECT

public:
	explicit StartGameTab(QWidget *parent, Launcher *launcher, AccountPool *accountPool, ProfileManager *profileManager);
	~StartGameTab();

	void changeEvent(QEvent *event);

private slots:
	void on_start_pb_clicked();

private:
	Ui::StartGameTab *ui_;
	Launcher *launcher_;
	AccountPool *accountPool_;
	ProfileManager *profileManager_;
};

#endif // STARTGAMETAB_H
