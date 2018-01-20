#include "LaunchAuth.h"

#include <QSettings>
#include <QUuid>

LaunchAuth::LaunchAuth(QObject *parent, Mode authMode) :
	GenericAuth(parent),
	authMode_(authMode)
{
//	if(mode == Mode::Online && !this->validate())
//		mode = Mode::Offline;//auto offline mode
}

bool LaunchAuth::validate() const
{
	QByteArray data = tokenStyle.arg(settings_.value("accessToken").toString())
					  .arg(settings_.value("clientToken").toString()).toUtf8();

	this->sendRequest(Invalidate, data);
	return success_;
}

QString LaunchAuth::getUserType() const
{
	return authMode_ == Mode::Online?
				"mojang":
				"Legacy";
}

QString LaunchAuth::getAuthUuid() const
{
	return authMode_ == Mode::Online?
				settings_.value("uuid").toString():
				"${auth_uuid}";
}

QString LaunchAuth::getAuthAccessToken() const
{
	return authMode_ == Mode::Online?
				settings_.value("accessToken").toString():
				"${auth_access_token}";
}

Mode LaunchAuth::getAuthMode() const
{
	return authMode_;
}
