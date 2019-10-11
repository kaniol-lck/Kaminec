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
	explicit JavaTab(QWidget *parent = nullptr);

	void accepted();

	~JavaTab();

private slots:
	void on_javaPath_showPb_clicked();

    void on_addArg_pushButton_clicked();

    void on_removeArg_pushButton_clicked();

private:
	Ui::JavaTab *ui_;
	Custom custom_;
};

#endif // JAVATAB_H
