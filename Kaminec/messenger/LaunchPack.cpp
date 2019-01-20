#include "LaunchPack.h"

LaunchPack::LaunchPack(Mode mode,
					   QStringList classPaths,
					   QStringList JVMArguments,
					   QString mainClass,
					   QStringList gameArguments,
					   QStringList versionChain,
					   QStringList nativesFiles) :
	mode_(mode),
	classPaths_(classPaths),
	JVMConfigure_(JVMArguments),
	mainClass_(mainClass),
	gameArguments_(gameArguments),
	versionChain_(versionChain),
	nativesFiles_(nativesFiles)
{}

QStringList LaunchPack::classPaths() const
{
	return classPaths_;
}

QStringList LaunchPack::JVMConfigure() const
{
	return JVMConfigure_;
}

QString LaunchPack::mainClass() const
{
	return mainClass_;
}

QStringList LaunchPack::gameArguments() const
{
	return gameArguments_;
}

QStringList LaunchPack::versionChain() const
{
	return versionChain_;
}

QStringList LaunchPack::nativesFiles() const
{
	return nativesFiles_;
}

QStringList LaunchPack::startCode() const
{
	QStringList startcode;
	startcode << JVMConfigure_;
	startcode << classPaths_.join(";");
	startcode << mainClass_;
	startcode << gameArguments_;

	return startcode;
}
