#include "LaunchAuth.h"

#include <QSettings>
#include <QUuid>

LaunchAuth::LaunchAuth(QObject *parent, Mode mode) :
	GenericAuth(parent),
	authMode(mode)
{
//	if(mode == Mode::Online && !this->validate())
//		mode = Mode::Offline;//auto offline mode
}

bool LaunchAuth::validate() const
{
	QByteArray data = tokenStyle.arg(settings.value("accessToken").toString())
					  .arg(settings.value("clientToken").toString()).toUtf8();

	this->sendRequest(Invalidate, data);
	return success;
}

QString LaunchAuth::getUserType() const
{
	return authMode == Mode::Online?
				"mojang":
				"Legacy";
}

QString LaunchAuth::getAuthUuid() const
{
	return authMode == Mode::Online?
				settings.value("uuid").toString():
				"${auth_uuid}";
}

QString LaunchAuth::getAuthAccessToken() const
{
	return authMode == Mode::Online?
				settings.value("accessToken").toString():
				"${auth_access_token}";
}

Mode LaunchAuth::getAuthMode() const
{
	return authMode;
}
