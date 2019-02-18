#ifndef RULE_H
#define RULE_H

#include <QVariant>

class Rule
{
public:
	using Action = bool;
	static const bool ALLOW = true;
	static const bool DISALLOW = false;

	Rule(const QVariant &rule);

	Action ruleAction() const;

	static bool checkFeature(const QString &key);

private:
	Action action_;

	QString osName_;
};

#endif // RULE_H
