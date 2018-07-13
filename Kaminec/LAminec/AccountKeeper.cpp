#include "AccountKeeper.h"

AccountKeeper::AccountKeeper(QObject *parent, const Account &account) :
	QObject(parent),
	authResponse_(new AuthResponse(parent)),
	account_(account),
	authkit_(authResponse_)
{}

bool AccountKeeper::validate()
{
	QByteArray data = AuthKit::kTokenStyle.arg(account_.accessToken(),
											   account_.clientToken()).toUtf8();
	connect(authResponse_, SIGNAL(validateFinished(bool)), this, SLOT(validateFinished(bool)));
	authkit_.validate(data);
	disconnect(authResponse_, SIGNAL(validateFinished(bool)), this, SLOT(validateFinished(bool)));

	return success_;
}

Account AccountKeeper::getAccount() const
{
	return account_;
}

void AccountKeeper::validateFinished(bool)
{
	success_ = true;
}
