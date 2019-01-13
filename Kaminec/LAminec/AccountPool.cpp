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
	auto map = accountsObject_.value("accounts").toVariant().toMap();
	for(auto it = map.begin(); it != map.end(); it++){
		Account account(value(it.value(), "mode").toBool()?Mode::Online:Mode::Offline,
						value(it.value(), "email").toString(),
						value(it.value(), "uuid").toString(),
						value(it.value(), "accessToken").toString(),
						value(it.value(), "clientToken").toString(),
						value(it.value(), "playername").toString());
		accountsMap.insert(it.key(), account);
	}

	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(accountsFile_.fileName(), ok.errorString(), true);
}

Account AccountPool::check(const QString &accountId) const
{
	auto account = accountsMap.value(accountId);
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

bool AccountPool::initAccounts()
{
	auto accounts = accountsObject_.value("accounts").toObject();

	accounts.insert("default_account", QJsonObject{
						{"mode", false},
						{"playername", "Steve"}
					});

	accountsObject_.insert("accounts", accounts);

	if(!accountsFile_.open(QIODevice::WriteOnly | QIODevice::Text))return false;
	QTextStream out(&accountsFile_);
	auto bytes = QJsonDocument(accountsObject_).toJson();
	out<<bytes;
	accountsFile_.close();

	return true;
}

QMap<QString, Account> AccountPool::getAccounts()
{
	return accountsMap;
}
Account AccountPool::getAccount(const QString &accountId) const
{
	for(auto account : accountsMap)
		if(account.id() == accountId){
			return account;
		}
	return Account();
}

bool AccountPool::containAccount(const QString &accountId) const
{
	bool isContain = false;

	for(auto account : accountsMap)
		if(account.id() == accountId){
			isContain = true;
		}
	return isContain;
}

bool AccountPool::insertAccount(const Account &account)
{
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

	return true;
}

void AccountPool::setSelectedAccountId(const QString &id)
{
	custom_.setSelectedAccountId(id);
}

QString AccountPool::getSelectedAccountId()
{
	return custom_.getSelectedAccountId();
}

void AccountPool::validateFinished(bool success)
{
	success_ = success;
}
