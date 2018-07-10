#ifndef LAUNCHPARSER_H
#define LAUNCHPARSER_H

#include "messager/Profile.h"
#include "launch/LaunchJson.h"
#include "assistance/Custom.h"
#include "messager/LaunchPack.h"
#include "messager/Account.h"

class LaunchParser
{
public:
	LaunchParser(const Profile &profile, const Account &account);

	LaunchPack getLaunchPack() const;

private:
	QStringList JVMConfigure() const;
	QStringList gameArguments() const;

	QStringList classPaths() const;
	QString mainClass() const;

	QStringList versionChain() const;

	QStringList nativesFiles() const;

private:
	Profile profile_;
	Account account_;
	LaunchJson launchJson_;
	Custom custom_;

};

#endif // LAUNCHPARSER_H
