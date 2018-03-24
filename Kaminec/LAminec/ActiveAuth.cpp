#include "ActiveAuth.h"
#include "assistance/utility.h"

ActiveAuth::ActiveAuth(QObject *parent) :
	QObject(parent)
{}

bool ActiveAuth::authenticate(const QString &username, const QString &password) const
{
	QByteArray data = AuthKit::kAuthenticateStyle.arg(username).arg(password).toUtf8();

	return authKit_.authenticate(data);
}

bool ActiveAuth::refresh() const
{
	QByteArray data = AuthKit::kTokenStyle.arg(custom_.getAccessToken())
					  .arg(custom_.getClientToken()).toUtf8();

	return authKit_.refresh(data);
}

bool ActiveAuth::invalidate() const
{
	QByteArray data = AuthKit::kTokenStyle.arg(custom_.getAccessToken())
					  .arg(custom_.getClientToken()).toUtf8();

	return authKit_.invalidate(data);
}
