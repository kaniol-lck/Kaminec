#ifndef ACCOUNTPOOL_H
#define ACCOUNTPOOL_H

#include "LAminec/AccountKeeper.h"

#include <QObject>
#include <QFile>
#include <QJsonObject>

class AccountPool : public QObject
{
	Q_OBJECT
public:
	explicit AccountPool(QObject *parent = nullptr);

	void validateAll();

	void initAccounts();
	void addAccount(const Account &account);

private:
	QFile accountsFile_;
	QList<AccountKeeper*> validators;
	QJsonObject accountsObject_;

};

#endif // ACCOUNTPOOL_H
