#include "LogCleaner.h"

#include "assistance/Custom.h"
#include "assistance/Path.h"
#include "assistance/utility.h"

#include <QDir>
#include <QDebug>

LogCleaner::LogCleaner(QObject *parent) : QObject(parent)
{}

void LogCleaner::clean()
{
	QDir dir(Path::logsPath());
	auto leaveNumber = Custom().getLogFileNumber();

	//do nothing if no any logs here or no limit for logs
	if (!dir.exists() || leaveNumber == -1) return;

	dir.setFilter(QDir::Files);
	dir.setSorting(QDir::Name);

	//for instance : 2018-05-05-3.log.gz
	QRegExp regExp(R"(^20[1-9][0-9]-(0[1-9]|1[0-2])-((0[1-9])|((1|2)[0-9])|30|31)-\d+\.log\.gz$)");
	//=-=-=-=-=-=-=-=-=↑for 21 century

	auto count = 0;
	for(auto fileInfo : dir.entryInfoList()){
		if(regExp.exactMatch(fileInfo.fileName())){
			count++;
			if(count > leaveNumber)
				fileInfo.dir().remove(fileInfo.fileName());
		}
	}
}
