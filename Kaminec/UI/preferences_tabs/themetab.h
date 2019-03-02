#ifndef THEMETAB_H
#define THEMETAB_H

#include "assistance/Custom.h"

#include <QWidget>

namespace Ui {
	class ThemeTab;
}

class ThemeTab : public QWidget
{
	Q_OBJECT

public:
	explicit ThemeTab(QWidget *parent = 0);

	void accepted();

	~ThemeTab();

signals:
	void updateBackground();

private slots:
	void on_font_pb_clicked();

	void on_background_showPb_clicked();

	void updateFont();

private:
	Ui::ThemeTab *ui_;
	Custom custom_;
};

#endif // THEMETAB_H
