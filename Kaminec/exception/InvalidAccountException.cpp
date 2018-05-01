#include "InvalidAccountException.h"

InvalidAccountException::InvalidAccountException(QString accountName) :
	Exception("Invalid Account",
			  QString("Please check your account:%1.").arg(accountName))
{}
