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

	void validate();
	void refresh();

private:
	AuthResponse *authResponse_;
	Account account_;
	AuthKit authkit_;

};

#endif // ACCOUNTKEEPER_H
