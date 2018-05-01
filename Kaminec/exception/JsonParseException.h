#ifndef JSONPARSEEXCEPTION_H
#define JSONPARSEEXCEPTION_H

#include "exception/Exception.h"

class JsonParseException : public Exception
{
public:
	JsonParseException(QString jsonFileName);

};

#endif // JSONPARSEEXCEPTION_H
