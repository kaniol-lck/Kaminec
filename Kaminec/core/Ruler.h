#ifndef RULER_H
#define RULER_H

#include <QList>
#include <QVariant>

#include "assistance/utility.h"
#include "assistance/systeminfo.h"

class Ruler
{
public:
	Ruler(QVariant rule);

	bool isAllow();

private:
	enum Action{ Allow, Disallow };

	static Action reverseAction(const Action& action);

	//nested class Rule implementation
	class Rule{
	public:
		Rule(QVariant rule)
		{
			if(value(rule, "action").toString() == "allow"){
				action = Action::Allow;
			} else{
				action = Action::Disallow;
			}
			if(rule.toMap().contains("os")){
				osName = value(rule, "os", "name").toString();
				anyOS = false;
			} else{
				anyOS = true;
			}
		}

		bool ruleAction() const
		{
			if(anyOS && osName == sysName()){
				return action;
			}else {
				return reverseAction(action);
			}
		}
	private:
		Action action;

		bool anyOS;

		QString osName;

	};
	QList<Rule> mRuleList;
};

#endif // RULER_H
