#ifndef VALIDATEDIALOG_H
#define VALIDATEDIALOG_H

#include "assistance/Custom.h"

#include <QDialog>

namespace Ui {
	class ValidateDialog;
}

class ValidateDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ValidateDialog(QWidget *parent, const QString &email);
	~ValidateDialog();

signals:
	void login(QString email, QString password);

private slots:
	void on_buttonBox_accepted();

	void on_showPassword_pb_toggled(bool checked);

private:
	Ui::ValidateDialog *ui_;

};

#endif // VALIDATEDIALOG_H
