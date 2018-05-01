#include "JsonParseException.h"

JsonParseException::JsonParseException(QString jsonFileName) :
	Exception(QString("Can not parse json file : %1").arg(jsonFileName),
			  QString("Please check if the file is damaged."))
{}
