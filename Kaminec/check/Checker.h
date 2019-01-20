#ifndef CHECKER_H
#define CHECKER_H

#include "messenger/Deficiency.h"

#include <QObject>
#include <QString>

class Checker : QObject
{
public:
	explicit Checker(QObject *parent = nullptr);
	QList<Deficiency> check(const QString &version);

private:
	static Deficiency checkFile(const CheckInfo &checkInfo);

};

#endif // CHECKER_H
