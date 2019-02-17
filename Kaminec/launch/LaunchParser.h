#ifndef LAUNCHPARSER_H
#define LAUNCHPARSER_H

#include "messenger/Profile.h"
#include "launch/LaunchJson.h"
#include "assistance/Custom.h"
#include "messenger/LaunchPack.h"
#include "messenger/Account.h"

class LaunchParser
{
public:
	LaunchParser(const Profile &profile, const Account &account);

	LaunchPack getLaunchPack() const;

private:
	Arguments JVMConfigure() const;
	Arguments gameArguments() const;

	QStringList classPaths() const;
	QString mainClass() const;

	QList<GameVersion> versionChain() const;

	QStringList nativesFiles() const;

private:
	Profile profile_;
	Account account_;
	LaunchJson launchJson_;
	Custom custom_;

};

#endif // LAUNCHPARSER_H
