#ifndef ACCOUNTPOOL_H
#define ACCOUNTPOOL_H

#include "assistance/Custom.h"
#include "messenger/Account.h"
#include "kits/AuthKit/AuthKit.h"
#include "kits/AuthKit/AuthResponse.h"

#include <QObject>
#include <QFile>
#include <QJsonObject>
#include <QStandardItemModel>

class AccountPool : public QObject
{
	Q_OBJECT
public:
	explicit AccountPool(QObject *parent = nullptr);

	Account check(const QString& accountId) const;

	void validateAll();
	bool validate(const Account &account) const;

	void initAccounts();
	QMap<QString, Account> getAccounts();
	QStandardItemModel* getAccountsModel();
	QString idFromIndex(const QModelIndex &index);
	Account getAccount(const QString &accountId) const;
	bool containAccount(const QString &accountId) const;

	bool insertAccount(const Account &account);
	bool removeAccount(const QString &accountId);

	void setSelectedAccountId(const QString &accountId);
	QString getSelectedAccountId();

	QList<QStandardItem*> account2itemList(const Account &account);

public slots:
	void validateFinished(bool succuss);

private:
	QFile accountsFile_;
	QMap<QString, Account> accountsMap_;
	QStringList accountIdList;
	QStandardItemModel model_;
	QJsonObject accountsObject_;
	Custom custom_;
	AuthResponse* authResponse_;
	AuthKit authKit_;
	bool success_ = false;
};

#endif // ACCOUNTPOOL_H
