#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(QString fileName) :
	Exception(QString("Need %1!").arg(fileName),
			  QString("Please check your %1 again.").arg(fileName))
{}
