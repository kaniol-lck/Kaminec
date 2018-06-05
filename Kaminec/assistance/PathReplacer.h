#ifndef PATHREPLACER_H
#define PATHREPLACER_H

#include <QString>

class PathReplacer
{
public:
	static QString replace(QString &path);
	static QString replace(const QString &path);

};

#endif // PATHREPLACER_H
