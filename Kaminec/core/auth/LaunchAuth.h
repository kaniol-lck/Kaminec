#ifndef LAUNCHAUTH_H
#define LAUNCHAUTH_H

#include "core/auth/AuthKit.h"
#include "core/Gamemode.h"

#include <memory>

class LaunchAuth
{
public:
	LaunchAuth(Mode authMode);
	~LaunchAuth() = default;

	bool validate() const;

	QString getUserType() const;
	QString getAuthUuid() const;
	QString getAuthAccessToken() const;

	Mode getAuthMode() const;

private:
	AuthKit authKit_;
	Mode authMode_;
};

#endif // LAUNCHAUTH_H
