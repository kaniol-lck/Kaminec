#include "Profile.h"

Profile::Profile(const QString &name,
				 ProfileType type,
				 const GameVersion &lastVersionId,
				 const QString &gameDir,
				 QDateTime created,
				 QDateTime lastUsed) :
	name_(name),
	type_(type),
	lastVersionId_(lastVersionId),
	gameDir_(gameDir),
	created_(created),
	lastUsed_(lastUsed)
{}

QString Profile::name() const
{
	return name_;
}

ProfileType Profile::type() const
{
	return type_;
}

GameVersion Profile::lastVersionId() const
{
	return lastVersionId_;
}

QString Profile::gameDir() const
{
    return gameDir_;
}

QDateTime Profile::created() const
{
	return created_;
}

QDateTime Profile::lastUsed() const
{
	return lastUsed_;
}

void Profile::setLastUsed(const QDateTime &lastUsed)
{
	lastUsed_ = lastUsed;
}
