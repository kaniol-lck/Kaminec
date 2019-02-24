#ifndef LAMINECTAB_H
#define LAMINECTAB_H

#include "assistance/Custom.h"

#include <QWidget>

namespace Ui {
	class LauncherTab;
}

class LauncherTab : public QWidget
{
	Q_OBJECT

public:
	explicit LauncherTab(QWidget *parent = 0);

	void accepted();

	~LauncherTab();

private slots:
	void on_logNumber_spinBox_valueChanged(int arg1);

private:
	Ui::LauncherTab *ui_;
	Custom custom_;
};

#endif // LAMINECTAB_H
