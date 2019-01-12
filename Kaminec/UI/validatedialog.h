#ifndef VALIDATEDIALOG_H
#define VALIDATEDIALOG_H

#include "assistance/Custom.h"
#include "messager/Account.h"
#include "kits/AuthKit/AuthKit.h"

#include <QDialog>

namespace Ui {
	class ValidateDialog;
}

class ValidateDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ValidateDialog(QWidget *parent);
	~ValidateDialog();

signals:
	void resultAccount(Account account);

private slots:
	void on_buttonBox_accepted();

	void on_showPassword_pb_toggled(bool checked);

	void on_login_pb_clicked();

	void on_online_rb_clicked();

	void on_offline_rb_clicked();

	void uuidUpdate(QString uuid);
	void accessTokenUpdate(QString accessToken);
	void clientTokenUpdate(QString clientToken);
	void playerNameUpdate(QString playername);
	void authenticateFinished(bool ok);
	void authError(QString error, QString errorMessage);

private:
	Ui::ValidateDialog *ui_;
	AuthResponse *authResponse_;
	AuthKit authkit_;
	//invisible attributes
	QString uuid_;
	QString accessToken_;
	QString clientToken_;
	bool success_ = false;

};

#endif // VALIDATEDIALOG_H
