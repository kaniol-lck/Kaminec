#ifndef VALIDATEDIALOG_H
#define VALIDATEDIALOG_H

#include "assistance/Custom.h"
#include "messenger/Account.h"
#include "kits/AuthKit/AuthKit.h"
#include "LAminec/AccountPool.h"

#include <QDialog>

namespace Ui {
	class ValidateDialog;
}

class ValidateDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ValidateDialog(QWidget *parent, AccountPool *accountPool);
	explicit ValidateDialog(QWidget *parent, AccountPool *accountPool, const Account &account);
	~ValidateDialog();

signals:

private slots:
	void on_buttonBox_accepted();

	void on_showPassword_pb_toggled(bool checked);

	void on_log_in_out_pb_clicked();

	void on_online_rb_clicked();

	void on_offline_rb_clicked();

	void uuidUpdate(QString uuid);
	void accessTokenUpdate(QString accessToken);
	void clientTokenUpdate(QString clientToken);
	void playerNameUpdate(QString playername);
	void authFinished(bool ok);
	void authError(QString error, QString errorMessage);

private:
	Ui::ValidateDialog *ui_;
	AuthResponse *authResponse_;
	AuthKit authkit_;
	AccountPool *accountPool_;
	//invisible attributes
	QString uuid_;
	QString accessToken_;
	QString clientToken_;
	Account account_;
	bool success_ = false;
	bool isValidated = false;
};

#endif // VALIDATEDIALOG_H
