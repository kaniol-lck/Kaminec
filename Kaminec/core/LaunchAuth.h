#ifndef LAUNCHAUTH_H
#define LAUNCHAUTH_H

#include "core/GenericAuth.h"
#include "core/Gamemode.h"

#include <QSettings>

class LaunchAuth final: public GenericAuth
{
public:
	LaunchAuth(QObject *parent, Mode authMode);
	~LaunchAuth() = default;

	bool validate() const;

	QString getUserType() const;
	QString getAuthUuid() const;
	QString getAuthAccessToken() const;

	Mode getAuthMode() const;

private:
	QSettings settings;
	Mode authMode;
};

#endif // LAUNCHAUTH_H
