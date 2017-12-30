#ifndef PREFERENCE_H
#define PREFERENCE_H

#include "LAminec/ActiveAuth.h"

#include <QDialog>

namespace Ui {
	class Preference;
}

class Preference : public QDialog
{
	Q_OBJECT

public:
	explicit Preference(QWidget *parent, ActiveAuth *auth);
	~Preference();

private:
	QString getAutoJavaPath();

private slots:
	void on_corePath_showPb_clicked();

	void on_javaPath_showPb_clicked();

	void on_buttonBox_accepted();

	void on_login_pb_clicked();

	void logChanged(QString email);

	void on_autoName_cb_stateChanged(int arg1);

	void on_fullScreen_checkBox_stateChanged(int arg1);

	void on_more_pb_clicked();

private:
	Ui::Preference *ui;

	ActiveAuth *activeAuth;
	bool customPath = false;
};

#endif // PREFERENCE_H
