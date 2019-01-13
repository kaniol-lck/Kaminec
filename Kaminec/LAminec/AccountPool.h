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
	Account validate(const QString &id, bool &ok);

	bool initAccounts();
	QList<Account> getAccounts();
	QPair<bool, Account> getAccount(const QString &name, Mode mode);

	bool insertAccount(const Account &account);
	bool removeAccount(const QString &accountId);

	void setSelectedAccountId(const QString &id);
	QString getSelectedAccountId();

private:
	QFile accountsFile_;
	QMap<QString, AccountKeeper*> validators;
	QJsonObject accountsObject_;
	Custom custom_;
};

#endif // ACCOUNTPOOL_H
