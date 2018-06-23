#ifndef VALIDATEDIALOG_H
#define VALIDATEDIALOG_H

#include "LAminec/Validator.h"
#include "assistance/Custom.h"

#include <QDialog>

namespace Ui {
	class ValidateDialog;
}

class ValidateDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ValidateDialog(QWidget *parent, Validator *auth);
	~ValidateDialog();

signals:

	void login(QString username);

private slots:
	void on_buttonBox_accepted();

	void on_showPassword_pb_toggled(bool checked);

private:
	Ui::ValidateDialog *ui_;

	Validator *activeAuth_;
	Custom custom_;
	AuthKit authKit_;

	Account authenticate(const QString &email, const QString &password) const;

};

#endif // VALIDATEDIALOG_H
