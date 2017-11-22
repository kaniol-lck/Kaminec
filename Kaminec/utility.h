#ifndef UTILITY_H
#define UTILITY_H

template<typename Container, typename ... list>
inline QVariant value(const Container& c, const QString& s)
{
	return c.toMap().value(s);
}

template<typename Container, typename ... list>
inline QVariant value(const Container& c, const  QString& s, const list&... Args)
{
	return value(c.toMap().value(s), Args...);
}

#include <QString>
#include <QStringList>
QString genFilename(const QString& name)
{
	auto list = name.split(":");
	return QString(list.at(0)).replace('.','/') + "/" +
			list.at(1) + "/" +
			list.at(2) + "/" +
			list.at(1) + "-" +
			list.at(2) + ".jar";
}
#endif // UTILITY_H
