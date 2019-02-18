#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "UI/preferences_tabs/javatab.h"
#include "UI/preferences_tabs/gametab.h"
#include "UI/preferences_tabs/pathtab.h"
#include "UI/preferences_tabs/laminectab.h"
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

signals:
	void settingfinished();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::Preferences *ui_;
	AccountPool *accountPool_;
	ProfileManager *profileManager_;

	JavaTab *javaTab_;
	GameTab *gameTab_;
	PathTab *pathTab_;
	LAminecTab *lAminecTab_;
};

#endif // PREFERENCES_H
