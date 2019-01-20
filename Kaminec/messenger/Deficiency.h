#ifndef DEFICIENCY_H
#define DEFICIENCY_H

#include "messenger/CheckInfo.h"

#include <QString>

struct Deficiency
{
	enum Type{ NotExist, WrongCheckCode, OpenError };

	Deficiency() = default;
	Deficiency(bool ok);
	Deficiency(const QString &fileName, const QString &path, Type type, const QUrl url);
	Deficiency(const CheckInfo &checkInfo, Type type);

	bool ok_ = false;

	QString fileName_;
	QString path_;
	Type type_;
	QUrl url_;
};

#endif // DEFICIENCY_H
