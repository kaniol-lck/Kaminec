#ifndef CHECKER_H
#define CHECKER_H

#include <QString>

#include "messager/Deficiency.h"

class Checker
{
public:
	QList<Deficiency> check(const QString &version);

private:
	static Deficiency checkFile(const CheckInfo &checkInfo);

};

#endif // CHECKER_H
