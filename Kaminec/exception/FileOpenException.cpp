#include "FileOpenException.h"

FileOpenException::FileOpenException(QString fileName) :
	Exception(QString("Cannot open %1!").arg(fileName),
			  QString("Please check if the file is occupied:%1").arg(fileName))
{}
