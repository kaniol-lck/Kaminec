#include "profile.h"

Profile::Profile(const QString &name,
				 ProfileType type,
				 const QString &lastVersionId,
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

QString Profile::lastVersionId() const
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

void Profile::setlastUsed(const QDateTime &lastUsed)
{
	lastUsed_ = lastUsed;
}
