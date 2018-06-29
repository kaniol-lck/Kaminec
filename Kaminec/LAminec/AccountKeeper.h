#ifndef ACCOUNTKEEPER_H
#define ACCOUNTKEEPER_H

#include "messager/Account.h"
#include "kits/AuthKit/AuthKit.h"

#include <QObject>

class AccountKeeper : public QObject
{
	Q_OBJECT
public:
	explicit AccountKeeper(QObject *parent, const Account &account);

	bool validate();
	void refresh();

private:
	Account account_;
	AuthKit authkit_;

};

#endif // ACCOUNTKEEPER_H
