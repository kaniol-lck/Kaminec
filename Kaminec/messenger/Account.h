#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "assistance/Gamemode.h"

#include <QDateTime>
#include <QUuid>

class Account
{
public:
	explicit Account(const QString &playername = "Steve",
					 Mode mode = Mode::Uncertified,
					 const QString &email = "",
					 const QString &uuid = "",
					 const QString &accessToken = "",
					 const QDateTime &created = QDateTime::currentDateTime(),
					 const QDateTime &lastUsed = QDateTime());

	QString name() const;
	QString playername() const;
	Mode mode() const;
	QString email() const;
	QString uuid() const;
	QString accessToken() const;
	QDateTime created() const;
	QDateTime lastUsed() const;

	void setLastUsed(const QDateTime &lastUsed);

private:
	QString playername_;
	Mode mode_;
	QString email_;
	QString uuid_;
	QString accessToken_;
	QDateTime created_;
	QDateTime lastUsed_;
};

#endif // ACCOUNT_H
