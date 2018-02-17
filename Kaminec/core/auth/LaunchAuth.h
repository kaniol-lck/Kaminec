#ifndef LAUNCHAUTH_H
#define LAUNCHAUTH_H

#include "core/auth/AuthKit.h"
#include "core/Gamemode.h"

#include <memory>
#include <QSettings>

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
	std::shared_ptr<AuthKit> authKit_;
	std::shared_ptr<QSettings> settings_;
	Mode authMode_;
};

#endif // LAUNCHAUTH_H
