#ifndef VALIDATEDIALOG_H
#define VALIDATEDIALOG_H

#include "LAminec/ActiveAuth.h"
#include "core/Custom.h"

#include <QDialog>

namespace Ui {
	class ValidateDialog;
}

class ValidateDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ValidateDialog(QWidget *parent, ActiveAuth *auth);
	~ValidateDialog();

signals:

	void login(QString username);

private slots:
	void on_buttonBox_accepted();

	void on_showPassword_pb_toggled(bool checked);

private:
	Ui::ValidateDialog *ui_;

	ActiveAuth *activeAuth_;
	Custom custom_;
};

#endif // VALIDATEDIALOG_H
