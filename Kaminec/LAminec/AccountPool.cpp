#include "AccountPool.h"

#include "assistance/PathReplacer.h"
#include "assistance/utility.h"
#include "exception/Exceptions.hpp"

#include <QJsonDocument>
#include <QJsonObject>

AccountPool::AccountPool(QObject *parent) :
	QObject(parent),
	accountsFile_(PathReplacer::replace("<launcher>/accounts.json"))
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
		validators.insert(it.key(), new AccountKeeper(this, account));
	}

	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(accountsFile_.fileName(), ok.errorString(), true);
}

Account AccountPool::validate(const QString &id, bool &ok)
{
	if(!validators.contains(id)){}
	if(validators.value(id)->validate()){
		ok = true;
		return validators.value(id)->getAccount();
	}
	ok = false;
	return Account();
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

QList<Account> AccountPool::getAccounts()
{
	QList<Account> accounts;
	for(auto validator : validators)
		accounts.append(validator->getAccount());
	return accounts;
}
QPair<bool, Account> AccountPool::getAccount(const QString &name, Mode mode)
{
	for(const auto& accountVariant : accountsObject_.value("accounts").toVariant().toMap())
		if(value(accountVariant, "playername").toString() == name &&
		   value(accountVariant, "mode").toBool() == (mode == Mode::Online))
			return qMakePair(true,
							 Account(value(accountVariant, "mode").toBool()? Mode::Online : Mode::Offline,
									 value(accountVariant, "email").toString(),
									 value(accountVariant, "accessToken").toString(),
									 value(accountVariant, "clientToken").toString(),
									 value(accountVariant, "playername").toString()));
	return qMakePair(false, Account());
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
