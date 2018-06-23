#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "assistance/Gamemode.h"

#include <QString>

class Account
{
public:
	Account(Mode mode,
			const QString &email,
			const QString &accessToken,
			const QString &clientToken,
			const QString &username);

	Mode mode() const;
	QString email() const;
	QString accessToken() const;
	QString clientToken() const;
	QString username() const;

private:
	Mode mode_;
	QString email_;
	QString accessToken_;
	QString clientToken_;
	QString username_;

};

#endif // ACCOUNT_H
