#ifndef LAUNCHAUTH_H
#define LAUNCHAUTH_H

#include "core/auth/AuthKit.h"
#include "core/Gamemode.h"

#include <QSettings>

class LaunchAuth
{
public:
	LaunchAuth(Mode authMode);
	~LaunchAuth();

	bool validate() const;

	QString getUserType() const;
	QString getAuthUuid() const;
	QString getAuthAccessToken() const;

	Mode getAuthMode() const;

private:
	AuthKit *authKit_;
	QSettings *settings_;
	Mode authMode_;
};

#endif // LAUNCHAUTH_H
