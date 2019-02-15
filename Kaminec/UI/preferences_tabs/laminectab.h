#ifndef LAMINECTAB_H
#define LAMINECTAB_H

#include "assistance/Custom.h"

#include <QWidget>

namespace Ui {
	class LAminecTab;
}

class LAminecTab : public QWidget
{
	Q_OBJECT

public:
	explicit LAminecTab(QWidget *parent = 0);

	void accepted();

	~LAminecTab();

private slots:
	void on_logNumber_spinBox_valueChanged(int arg1);

private:
	Ui::LAminecTab *ui_;
	Custom custom_;
};

#endif // LAMINECTAB_H
