#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include "assistance/Custom.h"
#include "messenger/Account.h"
#include "kits/AuthKit/AuthKit.h"
#include "LAminec/AccountPool.h"

#include <QDialog>
#include <memory>

namespace Ui {
	class AccountDialog;
}

class AccountDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AccountDialog(QWidget *parent, AccountPool *accountPool);
	explicit AccountDialog(QWidget *parent, AccountPool *accountPool, const QString &accountName);
	~AccountDialog();

signals:
	void newAccount(Account account);

private slots:
	void on_buttonBox_accepted();

	void on_showPassword_pb_toggled(bool checked);

	void on_log_in_out_pb_clicked();

	void on_certified_rb_clicked();

	void on_uncertified_rb_clicked();

	void uuidUpdate(QString uuid);
	void accessTokenUpdate(QString accessToken);
	void clientTokenUpdate(QString clientToken);
	void playerNameUpdate(QString playername);

private:
	Ui::AccountDialog *ui_;
	AuthResponse *authResponse_;
	AuthKit authkit_;
	AccountPool *accountPool_;
	QString uuid_;
	QString accessToken_;
	QString clientToken_;
	std::shared_ptr<Account> oldAccount_;
	bool success_ = false;
	bool isValidated = false;
};

#endif // ACCOUNTDIALOG_H
