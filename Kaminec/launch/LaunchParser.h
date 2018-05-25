#ifndef LAUNCHPARSER_H
#define LAUNCHPARSER_H

#include "messager/Profile.h"
#include "launch/LaunchAuth.h"
#include "launch/LaunchJson.h"
#include "assistance/Custom.h"
#include "messager/LaunchPack.h"

class LaunchParser
{
public:
	LaunchParser(const Profile &profile, const LaunchAuth &auth);

	LaunchPack getLaunchPack();

private:
	QStringList JVMConfigure();
	QStringList gameArguments();

	QStringList classPaths();
	QString mainClass();

	QStringList versionChain();

	QStringList nativesFiles();

private:
	Profile profile_;
	LaunchAuth launchAuth_;
	LaunchJson launchJson_;
	Custom custom_;

};

#endif // LAUNCHPARSER_H
