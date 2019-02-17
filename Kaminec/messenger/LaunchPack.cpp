#include "LaunchPack.h"

LaunchPack::LaunchPack(Mode mode,
					   QStringList classPaths,
					   Arguments JVMArguments,
					   QString mainClass,
					   Arguments gameArguments,
					   QList<GameVersion> versionChain,
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

Arguments LaunchPack::JVMConfigure() const
{
	return JVMConfigure_;
}

QString LaunchPack::mainClass() const
{
	return mainClass_;
}

Arguments LaunchPack::gameArguments() const
{
	return gameArguments_;
}

QList<GameVersion> LaunchPack::versionChain() const
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
	startcode << JVMConfigure_.toStringList();
	startcode << "-cp" << classPaths_.join(";");
	startcode << mainClass_;
	startcode << gameArguments_.toStringList();

	return startcode;
}
