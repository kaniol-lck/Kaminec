#include "Account.h"

Account::Account(Mode mode,
				 const QString &email,
				 const QString &accessToken,
				 const QString &clientToken,
				 const QString &username) :
	mode_(mode),
	email_(email),
	accessToken_(accessToken),
	clientToken_(clientToken),
	username_(username)
{}
