#ifndef UTILITY_H
#define UTILITY_H

template<typename Container, typename ... list>
QVariant value(Container c, QString s)
{
	return c.toMap().value(s);
}

template<typename Container, typename ... list>
QVariant value(Container c, QString s, list... Args)
{
	return value(c.toMap().value(s), Args...);
}

#endif // UTILITY_H
