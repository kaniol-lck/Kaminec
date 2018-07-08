#ifndef ACCOUNTPOOL_H
#define ACCOUNTPOOL_H

#include "LAminec/AccountKeeper.h"
#include "assistance/Custom.h"

#include <QObject>
#include <QFile>
#include <QJsonObject>

class AccountPool : public QObject
{
	Q_OBJECT
public:
	explicit AccountPool(QObject *parent = nullptr);

	void validateAll();

	void initAccounts(const Account &account = Account());
	Account getAccount(const QString &name);
	void addAccount(const Account &account);

	bool setSelectedAccount(const QString &id);
	Account getSelectedAccount();

private:
	QFile accountsFile_;
	QList<AccountKeeper*> validators;
	QJsonObject accountsObject_;
	Custom custom_;
};

#endif // ACCOUNTPOOL_H
