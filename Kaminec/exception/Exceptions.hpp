#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "exception/JsonParseException.h"

#define DEFINE_EXCEPTION(className, infoParameter, stringTitle, stringMessage) \
	class className : public Exception{\
	public:\
		className(const QString &infoParameter) : \
			Exception(QString(stringTitle).arg(infoParameter),\
					  QString(stringMessage).arg(infoParameter))\
		{}\
	};

DEFINE_EXCEPTION(DownloadException, message, "Need %1!", "Please check your %1 again.")
DEFINE_EXCEPTION(FileNotFoundException, fileName, "Need %1!", "Please check your %1 again.")
DEFINE_EXCEPTION(FileOpenException, message, "Cannot open %1!", "Please check if the file is occupied:%1")
DEFINE_EXCEPTION(InvalidAccountException, accountName, "Invalid Account", "Please check your account:%1.")

#include "exception/JsonParseException.h"

#undef DEFINE_EXCEPTION

#endif // EXCEPTIONS_H
