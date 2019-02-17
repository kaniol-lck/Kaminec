#include "assistance/utility.h"

#include <QDir>

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

QString formatTime(int ms)
{
	const int ss = 1000;
	const int mi = ss * 60;
	const int hh = mi * 60;
	const int dd = hh * 24;

	auto day = QString::number(ms / dd);
	ms %= dd;
	auto hour = QString::number(ms / hh);
	ms %= hh;
	auto minute = QString::number(ms / mi);
	ms %= mi;
	auto second = QString::number(ms / ss);
	ms %= ss;
	auto milliSecond = QString::number(ms);

	return QString("%1%2%3%4").arg(day=="0"?"" : day + "d",
								   hour=="0"?"" : hour + "h",
								   minute=="0"?"" : minute + "m",
								   second=="0"?"" : second + "s",
								   milliSecond=="0"?"" : milliSecond + "ms");
}
