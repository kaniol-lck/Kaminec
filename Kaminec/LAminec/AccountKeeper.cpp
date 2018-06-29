#include "AccountKeeper.h"

AccountKeeper::AccountKeeper(QObject *parent, const Account &account) :
	QObject(parent),
	account_(account)
{}

bool AccountKeeper::validate()
{
	QByteArray data = AuthKit::kTokenStyle.arg(account_.accessToken(),
											   account_.clientToken());
	authkit_.validate(data);

}
