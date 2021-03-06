#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "messenger/GameMode.h"

#include <QDateTime>
#include <QUuid>

class Account
{
public:
	explicit Account(const QString &playername = "Steve",
					 GameMode mode = GameMode::Uncertified,
					 const QString &email = "",
					 const QString &uuid = "",
					 const QString &accessToken = "",
					 const QDateTime &created = QDateTime::currentDateTime(),
					 const QDateTime &lastUsed = QDateTime());

	QString name() const;
	QString playername() const;
	GameMode mode() const;
	QString email() const;
	QString uuid() const;
	QString accessToken() const;
	QDateTime created() const;
	QDateTime lastUsed() const;

	void setLastUsed(const QDateTime &lastUsed);

private:
	QString playername_;
	GameMode mode_;
	QString email_;
	QString uuid_;
	QString accessToken_;
	QDateTime created_;
	QDateTime lastUsed_;
};

#endif // ACCOUNT_H
