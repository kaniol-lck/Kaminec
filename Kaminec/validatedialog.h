#ifndef VALIDATEDIALOG_H
#define VALIDATEDIALOG_H

#include <QDialog>

namespace Ui {
	class ValidateDialog;
}

class ValidateDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ValidateDialog(QWidget *parent = 0);
	~ValidateDialog();

signals:

	void login(QString username);

private slots:
	void on_showPassword_pb_clicked();

	void on_buttonBox_accepted();

private:
	Ui::ValidateDialog *ui;

	bool showPassword = false;
};

#endif // VALIDATEDIALOG_H
