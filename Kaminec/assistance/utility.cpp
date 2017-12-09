#include "utility.h"

QString genFilename(const QString& name)
{
	auto list = name.split(":");
	return QString("%1/%2/%3/%2-%3.jar")
			.arg(QString(list.at(0)).replace('.','/'))
			.arg(list.at(1))
			.arg(list.at(2));
}
