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

#endif // UTILITY_H
