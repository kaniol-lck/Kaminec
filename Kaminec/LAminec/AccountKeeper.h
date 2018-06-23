#ifndef ACCOUNTKEEPER_H
#define ACCOUNTKEEPER_H

#include "messager/Account.h"

#include <QObject>

class AccountKeeper : public QObject
{
	Q_OBJECT
public:
	explicit AccountKeeper(QObject *parent = nullptr);

	void refresh();
	void validate();

private:
	Account account_;

};

#endif // ACCOUNTKEEPER_H
