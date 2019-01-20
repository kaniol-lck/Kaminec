#ifndef ACCOUNTPOOL_H
#define ACCOUNTPOOL_H

#include "assistance/Custom.h"
#include "messenger/Account.h"
#include "kits/AuthKit/AuthKit.h"
#include "kits/AuthKit/AuthResponse.h"

#include <QObject>
#include <QFile>
#include <QJsonObject>

class AccountPool : public QObject
{
	Q_OBJECT
public:
	explicit AccountPool(QObject *parent = nullptr);

	Account check(const QString& accountId) const;

	void validateAll();
	bool validate(const Account &account) const;

	bool initAccounts();
	QMap<QString, Account> getAccounts();
	Account getAccount(const QString &accountId) const;
	bool containAccount(const QString &accountId) const;

	bool insertAccount(const Account &account);
	bool removeAccount(const QString &accountId);

	void setSelectedAccountId(const QString &id);
	QString getSelectedAccountId();

public slots:
	void validateFinished(bool succuss);

private:
	QFile accountsFile_;
	QMap<QString, Account> accountsMap;
	QJsonObject accountsObject_;
	Custom custom_;
	AuthResponse* authResponse_;
	AuthKit authKit_;
	bool success_ = false;
};

#endif // ACCOUNTPOOL_H
