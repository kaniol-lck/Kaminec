#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include "exception/Exception.h"

class FileNotFoundException : public Exception
{
public:
	FileNotFoundException(QString fileName);

};

#endif // FILENOTFOUNDEXCEPTION_H
