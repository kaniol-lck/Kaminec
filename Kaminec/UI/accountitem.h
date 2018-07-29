#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include "messager/Account.h"

#include <QWidget>

namespace Ui {
	class AccountItem;
}

class AccountItem : public QWidget
{
	Q_OBJECT

public:
	explicit AccountItem(QWidget *parent = 0, Account account = Account());


	~AccountItem();

private:
	Ui::AccountItem *ui;
};

#endif // ACCOUNTITEM_H
