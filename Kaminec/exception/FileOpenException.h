#ifndef FILEOPENEXCEPTION_H
#define FILEOPENEXCEPTION_H

#include "exception/Exception.h"

class FileOpenException : public Exception
{
public:
	FileOpenException(QString fileName);
};

#endif // FILEOPENEXCEPTION_H
