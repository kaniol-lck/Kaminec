#include "profile.h"

Profile::Profile(const QString &name,
				 const QString &lastVersionId,
				 const QString &gameDir):
	name_(name),
	lastVersionId_(lastVersionId),
	gameDir_(gameDir)
{}

QString Profile::name() const
{
	return name_;
}

QString Profile::lastVersionId() const
{
	return lastVersionId_;
}

QString Profile::gameDir() const
{
	return gameDir_;
}
