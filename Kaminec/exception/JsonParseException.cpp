#include "JsonParseException.h"

JsonParseException::JsonParseException(QString jsonFileName, QString errorString) :
	Exception(QString("Can not parse json file : %1").arg(jsonFileName),
			  errorString  + "Please check if the file is damaged.")
{}
