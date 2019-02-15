#ifndef JAVATAB_H
#define JAVATAB_H

#include "assistance/Custom.h"

#include <QWidget>

namespace Ui {
	class JavaTab;
}

class JavaTab : public QWidget
{
	Q_OBJECT

public:
	explicit JavaTab(QWidget *parent = 0);

	void accepted();

	~JavaTab();

private slots:
	void on_javaPath_showPb_clicked();

private:
	Ui::JavaTab *ui_;
	Custom custom_;
};

#endif // JAVATAB_H
