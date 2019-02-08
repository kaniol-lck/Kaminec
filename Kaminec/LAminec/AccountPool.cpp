#include "AccountPool.h"

#include "assistance/PathReplacer.h"
#include "assistance/utility.h"
#include "exception/Exceptions.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

AccountPool::AccountPool(QObject *parent) :
	QObject(parent),
	accountsFile_(PathReplacer::replace("<launcher>/accounts.json")),
	authResponse_(new AuthResponse(parent)),
	authKit_(authResponse_)
{
	model_.setColumnCount(3);
	model_.setHeaderData(0, Qt::Horizontal, "playername");
	model_.setHeaderData(1, Qt::Horizontal, "mode");
	model_.setHeaderData(2, Qt::Horizontal, "email");

	if(!accountsFile_.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug()<<"No content,auto make.";
		initAccounts();
	}
	QByteArray bytes = QString::fromLocal8Bit(accountsFile_.readAll()).toUtf8();
	accountsFile_.close();

	if(bytes.size()==0){
		qDebug()<<"No content,auto make.";
		initAccounts();
		return;
	}

	QJsonParseError ok;
	accountsObject_ = QJsonDocument::fromJson(bytes,&ok).object();
	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(accountsFile_.fileName(), ok.errorString(), true);

	auto map = accountsObject_.value("accounts").toVariant().toMap();
	for(auto it = map.begin(); it != map.end(); it++){
		Account account(value(it.value(), "mode").toBool()?Mode::Online:Mode::Offline,
						value(it.value(), "email").toString(),
						value(it.value(), "uuid").toString(),
						value(it.value(), "accessToken").toString(),
						value(it.value(), "clientToken").toString(),
						value(it.value(), "playername").toString());
		accountsMap_.insert(it.key(), account);
		accountIdList.append(it.key());

		model_.appendRow(account2itemList(account));
	}

	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(accountsFile_.fileName(), ok.errorString(), true);
}

Account AccountPool::check(const QString &accountId) const
{
	auto account = accountsMap_.value(accountId);
	if(account.mode() == Mode::Online){
		validate(account);
	} else{

	}
	return account;
}

bool AccountPool::validate(const Account &account) const
{
	QByteArray data = AuthKit::kTokenStyle.arg(account.accessToken(),
											   account.clientToken()).toUtf8();
	connect(authResponse_, SIGNAL(validateFinished(bool)), this, SLOT(validateFinished(bool)));
	authKit_.validate(data);
	disconnect(authResponse_, SIGNAL(validateFinished(bool)), this, SLOT(validateFinished(bool)));

	return success_;
}

void AccountPool::initAccounts()
{
	insertAccount(Account(Mode::Offline,"", "", "", "", "Steve"));
}

QMap<QString, Account> AccountPool::getAccounts()
{
	return accountsMap_;
}

QStandardItemModel *AccountPool::getAccountsModel()
{
	return &model_;
}

QString AccountPool::idFromIndex(const QModelIndex &index)
{
	return accountIdList.value(index.row());
}

Account AccountPool::getAccount(const QString &accountId) const
{
	for(auto account : accountsMap_)
		if(account.id() == accountId){
			return account;
		}
	return Account();
}

bool AccountPool::containAccount(const QString &accountId) const
{
	return accountIdList.contains(accountId);
}

bool AccountPool::insertAccount(const Account &account)
{
	accountsMap_.insert(account.id(), account);
	accountIdList.append(account.id());
	model_.appendRow(account2itemList(account));

	auto accounts = accountsObject_.value("accounts").toObject();

	if(account.mode()==Mode::Online){
		accounts.insert(account.id(), QJsonObject{
							{"mode", account.mode() == Mode::Online},
							{"email", account.email()},
							{"accessToken", account.accessToken()},
							{"clientToken", account.clientToken()},
							{"playername", account.playername()}
						});
	} else {
		accounts.insert(account.id(), QJsonObject{
							{"mode", account.mode() == Mode::Online},
							{"playername", account.playername()}
						});
	}

	accountsObject_.insert("accounts", accounts);

	if(!accountsFile_.open(QIODevice::WriteOnly | QIODevice::Text))return false;
	QTextStream out(&accountsFile_);
	auto bytes = QJsonDocument(accountsObject_).toJson();
	out<<bytes;
	accountsFile_.close();

	return true;
}

bool AccountPool::removeAccount(const QString &accountId)
{
	QJsonObject accounts = accountsObject_.value("accounts").toObject();

	accounts.remove(accountId);

	accountsObject_.insert("accounts", accounts);

	if(!accountsFile_.open(QIODevice::WriteOnly | QIODevice::Text))return false;
	QTextStream out(&accountsFile_);
	auto bytes = QJsonDocument(accountsObject_).toJson();
	out<<bytes;
	accountsFile_.close();

	auto index = accountIdList.indexOf(accountId);
	model_.removeRow(index);
	accountIdList.removeAt(index);
	accountsMap_.remove(accountId);
	return true;
}

void AccountPool::setSelectedAccountId(const QString &accountId)
{
	auto oldAccountId = getSelectedAccountId();
	custom_.setSelectedAccountId(accountId);

	auto row = accountIdList.indexOf(oldAccountId);
	model_.item(row, 0)->setCheckState(Qt::Unchecked);//remove check state

	row = accountIdList.indexOf(accountId);
	model_.item(row, 0)->setCheckState(Qt::Checked);//set check state
}

QString AccountPool::getSelectedAccountId()
{
	return custom_.getSelectedAccountId();
}

QList<QStandardItem *> AccountPool::account2itemList(const Account &account)
{
	auto playernameItem = new QStandardItem(account.playername());
	auto modelItem = new QStandardItem(account.mode() == Mode::Online?"online":"offline");
	auto emailItem = new QStandardItem(account.email());
	modelItem->setTextAlignment(Qt::AlignHCenter);
	playernameItem->setCheckable(false);
	playernameItem->setCheckState(getSelectedAccountId()==account.id()?Qt::Checked:Qt::Unchecked);

	return QList<QStandardItem*>{ playernameItem, modelItem, emailItem };
}

void AccountPool::validateFinished(bool success)
{
	success_ = success;
}
