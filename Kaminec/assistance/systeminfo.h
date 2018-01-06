#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QString>

#ifdef Q_OS_WIN
constexpr const char* sysName() { return "windows"; }
#endif

#ifdef Q_OS_LINUX
constexpr const char* sysName() { return "linux"; }
#endif

#ifdef Q_OS_MAC
constexpr const char* sysName() { return "osx"; }
#endif

constexpr int sysWordSize()
{
	return QSysInfo::WordSize;
}
#endif // SYSTEMINFO_H
