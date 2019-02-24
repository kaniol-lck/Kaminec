#include "Account.h"


Account::Account(const QString &playername,
				 Mode mode,
				 const QString &email,
				 const QString &uuid,
				 const QString &accessToken,
				 const QDateTime &created,
				 const QDateTime &lastUsed) :
	playername_(playername),
	mode_(mode),
	email_(email),
	uuid_(uuid),
	accessToken_(accessToken),
	created_(created),
	lastUsed_(lastUsed)
{}

QString Account::name() const
{
	return mode_==Mode::Certified?uuid_:playername_;
}

Mode Account::mode() const
{
	return mode_;
}

QString Account::email() const
{
	return email_;
}

QString Account::uuid() const
{
	return uuid_;
}

QString Account::accessToken() const
{
	return accessToken_;
}

QString Account::playername() const
{
	return playername_;
}

QDateTime Account::created() const
{
	return created_;
}

QDateTime Account::lastUsed() const
{
	return lastUsed_;
}

void Account::setLastUsed(const QDateTime &lastUsed)
{
	lastUsed_ = lastUsed;
}
