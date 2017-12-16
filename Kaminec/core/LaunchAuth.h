#ifndef LAUNCHAUTH_H
#define LAUNCHAUTH_H

#include "core/GenericAuth.h"
#include "core/Gamemode.h"

class LaunchAuth : public GenericAuth
{
public:
	LaunchAuth(QObject *parent, Mode mode);
	~LaunchAuth() = default;

};

#endif // LAUNCHAUTH_H
