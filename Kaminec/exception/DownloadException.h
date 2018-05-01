#ifndef DOWNLOADEXCEPTION_H
#define DOWNLOADEXCEPTION_H

#include "exception/Exception.h"

class DownloadException : public Exception
{
public:
	DownloadException(QString message);
};

#endif // DOWNLOADEXCEPTION_H
