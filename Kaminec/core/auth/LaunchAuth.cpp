#include "LaunchAuth.h"

#include <QSettings>

LaunchAuth::LaunchAuth(Mode authMode) :
	settings_(new QSettings(0)),
	authMode_(authMode)
{}

bool LaunchAuth::validate() const
{
	QByteArray data = AuthKit::kTokenStyle.arg(settings_->value("accessToken").toString())
					  .arg(settings_->value("clientToken").toString()).toUtf8();

	return authKit_.validate(data);
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
				settings_->value("uuid").toString():
				"${auth_uuid}";
}

QString LaunchAuth::getAuthAccessToken() const
{
	return authMode_ == Mode::Online?
				settings_->value("accessToken").toString():
				"${auth_access_token}";
}

Mode LaunchAuth::getAuthMode() const
{
	return authMode_;
}
