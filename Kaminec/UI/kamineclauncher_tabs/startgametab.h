#ifndef STARTGAMETAB_H
#define STARTGAMETAB_H

#include "LAminec/AccountPool.h"
#include "LAminec/ProfileManager.h"
#include "launch/Launcher.h"

#include <QWidget>

namespace Ui {
	class StartGameTab;
}

class StartGameTab : public QWidget
{
	Q_OBJECT

public:
	explicit StartGameTab(QWidget *parent, Launcher *launcher, AccountPool *accountPool, ProfileManager *profileManager);
	~StartGameTab();

	void changeEvent(QEvent *event);

private slots:
	void on_start_pb_clicked();

	void stateChanged(QProcess::ProcessState newState);
	void gameFinished(int i);
	void exceptionMessage(QString message);

private:
	Ui::StartGameTab *ui_;
	Launcher *launcher_;
	AccountPool *accountPool_;
	ProfileManager *profileManager_;
};

#endif // STARTGAMETAB_H
