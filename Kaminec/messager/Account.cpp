#include "Account.h"

Account::Account(Mode mode,
				 const QString &email,
				 const QString &accessToken,
				 const QString &clientToken,
				 const QString &playername) :
	mode_(mode),
	email_(email),
	accessToken_(accessToken),
	clientToken_(clientToken),
	playername_(playername)
{}

QString Account::id() const
{
	return QString("%1_%2_%3").arg(email(), playername(), mode());
}

Mode Account::mode() const
{
	return mode_;
}

QString Account::email() const
{
	return email_;
}

QString Account::accessToken() const
{
	return accessToken_;
}

QString Account::clientToken() const
{
	return clientToken_;
}

QString Account::playername() const
{
	return playername_;
}
