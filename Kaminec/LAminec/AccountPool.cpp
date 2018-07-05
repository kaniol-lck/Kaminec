#include "AccountPool.h"

#include "assistance/PathReplacer.h"
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
