#ifndef INVALIDACCOUNTEXCEPTION_H
#define INVALIDACCOUNTEXCEPTION_H

#include "exception/Exception.h"

class InvalidAccountException : public Exception
{
public:
	InvalidAccountException(QString accountName);
};

#endif // INVALIDACCOUNTEXCEPTION_H
