#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "assistance/Gamemode.h"

#include <QString>

class Account
{
public:
	explicit Account(Mode mode = Mode::Offline,
					 const QString &email = "",
					 const QString &uuid = "",
					 const QString &accessToken = "",
					 const QString &clientToken = "",
					 const QString &playername = "Steve");

	QString id() const;
	Mode mode() const;
	QString email() const;
	QString uuid() const;
	QString accessToken() const;
	QString clientToken() const;
	QString playername() const;

private:
	Mode mode_;
	QString email_;
	QString uuid_;
	QString accessToken_;
	QString clientToken_;
	QString playername_;

};

#endif // ACCOUNT_H
