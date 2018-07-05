#include "LaunchAuth.h"

#include "assistance/Custom.h"

#include <QEventLoop>

LaunchAuth::LaunchAuth(Mode authMode) :
	authResponse_(std::make_shared<AuthResponse>()),
	authKit_(authResponse_),
	authMode_(authMode)
{}

bool LaunchAuth::validate() const
{
	QByteArray data = AuthKit::kTokenStyle.arg(Custom().getAccessToken())
					  .arg(Custom().getClientToken()).toUtf8();

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
				Custom().getUuid():
				"${auth_uuid}";
}

QString LaunchAuth::getAuthAccessToken() const
{
	return authMode_ == Mode::Online?
				Custom().getAccessToken():
				"${auth_access_token}";
}

Mode LaunchAuth::getAuthMode() const
{
	return authMode_;
}
