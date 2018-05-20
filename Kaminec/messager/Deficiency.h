#ifndef DEFICIENCY_H
#define DEFICIENCY_H

#include "messager/CheckInfo.h"

#include <QString>

struct Deficiency
{
	enum Type{ NotExist, WrongCheckCode, OpenError };

	Deficiency() = default;
	Deficiency(bool ok);
	Deficiency(const QString &fileName, const QString &path, Type type);
	Deficiency(const CheckInfo &checkInfo, Type type);

	bool ok_ = false;

	QString fileName_;
	QString path_;
	Type type_;
};

#endif // DEFICIENCY_H
