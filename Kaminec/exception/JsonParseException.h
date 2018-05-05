#ifndef JSONPARSEEXCEPTION_H
#define JSONPARSEEXCEPTION_H

#include "exception/Exception.h"

class JsonParseException : public Exception
{
public:
	JsonParseException(QString jsonFileName, QString errorString, bool/*no name for distinction*/);
	JsonParseException(QString jsonName, QString errorString);

};

#endif // JSONPARSEEXCEPTION_H
