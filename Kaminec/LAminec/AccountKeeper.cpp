#include "AccountKeeper.h"

AccountKeeper::AccountKeeper(QObject *parent, const Account &account) :
	QObject(parent),
	authResponse_(new AuthResponse(parent)),
	account_(account),
	authkit_(authResponse_)
{}

void AccountKeeper::validate()
{
	QByteArray data = AuthKit::kTokenStyle.arg(account_.accessToken(),
											   account_.clientToken()).toUtf8();
	authkit_.validate(data);

}
