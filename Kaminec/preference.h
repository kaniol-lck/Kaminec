#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QDialog>

namespace Ui {
	class Preference;
}

class Preference : public QDialog
{
	Q_OBJECT

public:
	explicit Preference(QWidget *parent = 0);
	~Preference();

private:
	QString getAutoJavaPath();

private slots:
	void on_corePath_showPb_clicked();

	void on_javaPath_showPb_clicked();

	void on_buttonBox_accepted();

	void on_showPassword_pb_clicked();

private:
	Ui::Preference *ui;
	bool showPassword = false;
	QString notRealPassword = "It's not real password";
};

#endif // PREFERENCE_H
