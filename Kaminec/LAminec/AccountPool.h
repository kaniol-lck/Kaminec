#ifndef ACCOUNTPOOL_H
#define ACCOUNTPOOL_H

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
	bool validate(const Account &account) const;

	QStandardItemModel* getAccountsModel();

	void initAccounts();

	Account getAccount(const QString &accountId) const;
	QMap<QString, Account> getAccounts() const;
	bool containAccount(const QString &accountId) const;

	void insertAccount(const Account &account);
	void removeAccount(const QString &accountId);

	void setSelectedAccountId(const QString &accountId);
	QString getSelectedAccountId();

	void setAccountSorting(QString accountSorting);
	QString getAccountSorting() const;

	void setAccountAscending(bool accountAscending);
	bool getAccountAscending() const;

	QString idFromIndex(const QModelIndex &index) const;
	static QList<QStandardItem*> account2itemList(const Account &account);

	void sort(const QString &accountSorting, bool accountAscending);

	void writeToFile();

private slots:
	void validateFinished(bool succuss);

public slots:
	void sortRecord(int column);

private:
	QFile accountsFile_;
	QJsonObject accountsObject_;
	QMap<QString, Account> accountsMap_;
	AuthResponse* authResponse_;
	AuthKit authKit_;
	bool success_ = false;

	QStandardItemModel model_;
	enum Column{ Playername, Mode, Email, Id };
};

#endif // ACCOUNTPOOL_H
