#ifndef GAMEPARSER_H
#define GAMEPARSER_H

#include "messager/Profile.h"
#include "launch/LaunchAuth.h"
#include "launch/LaunchJson.h"
#include "assistance/Custom.h"

class GameParser
{
public:
	GameParser(const Profile &profile, const LaunchAuth &auth);

	QStringList getStartcode();

	QStringList getJVMArguments();
	QStringList getGameArguments();

	QString getClassPaths();

	QStringList getNativesPaths();

private:
	Profile profile_;
	LaunchAuth launchAuth_;
	LaunchJson launchJson_;
	Custom custom_;

};

#endif // GAMEPARSER_H
