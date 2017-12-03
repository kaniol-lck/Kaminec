#include "utility.h"

QString genFilename(const QString& name)
{
	auto list = name.split(":");
	return QString(list.at(0)).replace('.','/') + "/" +
			list.at(1) + "/" +
			list.at(2) + "/" +
			list.at(1) + "-" +
			list.at(2) + ".jar";
}
