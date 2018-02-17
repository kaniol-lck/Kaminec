#include "ActiveAuth.h"
#include "assistance/utility.h"

#include <QSettings>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>

ActiveAuth::ActiveAuth(QObject *parent) :
	QObject(parent),
	authKit_(new AuthKit(this))
{

}

bool ActiveAuth::authenticate(QString username, QString password) const
{
	QByteArray data = AuthKit::kAuthenticateStyle.arg(username).arg(password).toUtf8();

	return authKit_->authenticate(data);
}

bool ActiveAuth::refresh() const
{
	QByteArray data = AuthKit::kTokenStyle.arg(settings_.value("accessToken").toString())
					  .arg(settings_.value("clientToken").toString()).toUtf8();

	return authKit_->refresh(data);
}

bool ActiveAuth::invalidate() const
{
	QByteArray data = AuthKit::kTokenStyle.arg(settings_.value("accessToken").toString())
					  .arg(settings_.value("clientToken").toString()).toUtf8();

	return authKit_->invalidate(data);
}
