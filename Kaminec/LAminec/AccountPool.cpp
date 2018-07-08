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
	} else{
		QJsonParseError ok;
		accountsObject_ = QJsonDocument::fromJson(bytes,&ok).object();
		if(ok.error != QJsonParseError::NoError)
			throw JsonParseException(accountsFile_.fileName(), ok.errorString(), true);
	}
}

void AccountPool::initAccounts(const Account &account)
{
	profilesObject_ = QJsonObject{
		"accounts", QJsonObject{
			account.id(), QJsonObject{
				{"mode", account.mode() == Mode::Online},
				{"email", account.email()},
				{"accessToken", account.accessToken()},
				{"clientToken", account.clientToken()},
				{"playername", account.playername()}
			}
		}
	};
}
Account AccountPool::getAccount(const QString &name)
{
	for(const auto& accountVariant : profilesObject_.value("accounts").toVariant().toMap())
		if(value(accountVariant, "name").toString() == name)
			return Account(value(accountVariant, "mode").toBool()? Mode::Online : Mode::Offline,
						   value(accountVariant, "email").toString(),
						   value(accountVariant, "accessToken").toString(),
						   value(accountVariant, "clientToken").toString(),
						   value(accountVariant, "playername").toString());
	return Account();
}

bool AccountPool::setSelectedAccount(const QString &id)
{
	custom_.setSelectedAccountName(id);
}

Account AccountPool::getSelectedAccount()
{
	return getAccount(custom_.getSelectedAccountName());
}
