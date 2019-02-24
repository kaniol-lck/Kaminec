#ifndef ACCOUNTTAB_H
#define ACCOUNTTAB_H

#include "LAminec/AccountPool.h"

#include <QWidget>

namespace Ui {
	class AccountTab;
}

class AccountTab : public QWidget
{
	Q_OBJECT

public:
	explicit AccountTab(QWidget *parent, AccountPool *accountPool);
	~AccountTab();

	void changeEvent(QEvent *event);

private slots:
	void on_addAccount_pb_clicked();

	void on_deleteAccount_pb_clicked();

	void on_setAccountActive_pb_clicked();

	void accountSortRecord();

	void on_accounts_tableView_pressed(const QModelIndex &);

	void on_accounts_tableView_doubleClicked(const QModelIndex &index);

private:
	Ui::AccountTab *ui_;
	AccountPool *accountPool_;
};

#endif // ACCOUNTTAB_H
