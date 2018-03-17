#ifndef RULER_H
#define RULER_H

#include <QList>
#include <QVariant>

#include "assistance/utility.h"
#include "core/Rule.h"

class Ruler
{
public:
	Ruler(const QVariant &rule);

	bool isAllow();

private:
	QList<Rule> ruleList_;

};

#endif // RULER_H
