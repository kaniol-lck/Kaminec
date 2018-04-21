#ifndef LAUNCHPACK_H
#define LAUNCHPACK_H

#include <QStringList>

#include "assistance/Gamemode.h"

class LaunchPack
{
public:
	LaunchPack(Mode mode, QStringList classPaths,
			   QStringList JVMConfigure,
			   QString mainClass,
			   QStringList gameArguments,
			   QStringList versionChain,
			   QStringList nativesFiles);

	QStringList classPaths() const;
	QStringList JVMConfigure() const;
	QString mainClass() const;
	QStringList gameArguments() const;
	QStringList versionChain() const;
	QStringList nativesFiles() const;

	QStringList startCode() const;

private:
	Mode mode_;
	QStringList classPaths_;
	QStringList JVMConfigure_;
	QString mainClass_;
	QStringList gameArguments_;
	QStringList versionChain_;
	QStringList nativesFiles_;

};

#endif // LAUNCHPACK_H
