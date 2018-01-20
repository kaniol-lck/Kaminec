#include "ActiveAuth.h"
#include "assistance/utility.h"

#include <QSettings>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>

ActiveAuth::ActiveAuth(QObject *parent) :
	GenericAuth(parent)
{

}

bool ActiveAuth::authenticate(QString username, QString password) const
{
	QByteArray data = authenticateStyle.arg(username).arg(password).toUtf8();

	this->sendRequest(Authenticate, data);
	return success_;
}

bool ActiveAuth::refresh() const
{
	QByteArray data = tokenStyle.arg(settings_.value("accessToken").toString())
					  .arg(settings_.value("clientToken").toString()).toUtf8();

	this->sendRequest(Refresh, data);
	return success_;
}

bool ActiveAuth::invalidate() const
{
	QByteArray data = tokenStyle.arg(settings_.value("accessToken").toString())
					  .arg(settings_.value("clientToken").toString()).toUtf8();

	this->sendRequest(Invalidate, data);
	return success_;
}
