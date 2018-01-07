#include "utility.h"

#include <QDir>

QString genFilename(const QString& name)
{
	auto list = name.split(":");
	return QString("%1/%2/%3/%2-%3.jar")
			.arg(QString(list.at(0)).replace('.','/'))
			.arg(list.at(1))
			.arg(list.at(2));
}

bool deleteDirectory(const QString &path)
{
	if (path.isEmpty())
		return false;

	QDir dir(path);
	if(!dir.exists())
		return true;

	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
	QFileInfoList fileList = dir.entryInfoList();
	foreach (QFileInfo fi, fileList)
	{
		if (fi.isFile())
			fi.dir().remove(fi.fileName());
		else
			deleteDirectory(fi.absoluteFilePath());
	}
	return dir.rmpath(dir.absolutePath());
}
