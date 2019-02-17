#ifndef LAUNCHPACK_H
#define LAUNCHPACK_H

#include "assistance/Gamemode.h"
#include "messenger/Arguments.h"
#include "messenger/GameVersion.h"

class LaunchPack
{
public:
	LaunchPack(Mode mode,
			   QStringList classPaths,
			   Arguments JVMConfigure,
			   QString mainClass,
			   Arguments gameArguments,
			   QList<GameVersion> versionChain,
			   QStringList nativesFiles);

	QStringList classPaths() const;
	Arguments JVMConfigure() const;
	QString mainClass() const;
	Arguments gameArguments() const;
	QList<GameVersion> versionChain() const;
	QStringList nativesFiles() const;

	QStringList startCode() const;

private:
	Mode mode_;
	QStringList classPaths_;
	Arguments JVMConfigure_;
	QString mainClass_;
	Arguments gameArguments_;
	QList<GameVersion> versionChain_;
	QStringList nativesFiles_;

};

#endif // LAUNCHPACK_H
