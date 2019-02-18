#ifndef THEMETAB_H
#define THEMETAB_H

#include <QWidget>

namespace Ui {
	class ThemeTab;
}

class ThemeTab : public QWidget
{
	Q_OBJECT

public:
	explicit ThemeTab(QWidget *parent = 0);
	~ThemeTab();

private slots:
	void on_font_pb_clicked();

private:
	Ui::ThemeTab *ui_;
};

#endif // THEMETAB_H
