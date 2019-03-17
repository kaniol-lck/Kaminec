#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "assistance/Custom.h"

#include <QDialog>

class JavaTab;
class GameTab;
class PathTab;
class LauncherTab;
class ThemeTab;
class AccountPool;
class ProfileManager;

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
	void updateBackground();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::Preferences *ui_;
	AccountPool *accountPool_;
	ProfileManager *profileManager_;

	JavaTab *javaTab_;
	GameTab *gameTab_;
	PathTab *pathTab_;
	LauncherTab *launcherTab_;
	ThemeTab *themeTab_;
};

#endif // PREFERENCES_H
