#include "JsonParseException.h"

JsonParseException::JsonParseException(QString jsonFileName, QString errorString, bool) :
	Exception(QString("Can not parse json file : %1").arg(jsonFileName),
			  errorString  + "Please check if the file is damaged.")
{}

JsonParseException::JsonParseException(QString jsonName, QString errorString) :
	Exception(QString("Con not parse json from : %1").arg(jsonName),
			  errorString)
{}
