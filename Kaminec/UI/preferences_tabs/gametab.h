#ifndef GAMETAB_H
#define GAMETAB_H

#include "assistance/Custom.h"

#include <QWidget>

namespace Ui {
	class GameTab;
}

class GameTab : public QWidget
{
	Q_OBJECT

public:
	explicit GameTab(QWidget *parent = 0);

	void accepted();

	~GameTab();

private slots:
	void on_fullScreen_checkBox_stateChanged(int arg1);


private:
	Ui::GameTab *ui_;
	Custom custom_;
};

#endif // GAMETAB_H
