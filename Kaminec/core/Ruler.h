#ifndef RULER_H
#define RULER_H

#include <QList>
#include <QVariant>

#include "assistance/utility.h"
#include "assistance/systeminfo.h"

class Ruler
{
public:
	Ruler(const QVariant &rule);

	bool isAllow();

private:
	enum Action{ Allow, Disallow };

	static Action reverseAction(const Action& action);

	//nested class Rule implementation
	class Rule{
	public:
		Rule(const QVariant &rule)
		{
			if(value(rule, "action").toString() == "allow"){
				action_ = Action::Allow;
			} else{
				action_ = Action::Disallow;
			}
			if(rule.toMap().contains("os")){
				osName_ = value(rule, "os", "name").toString();
				anyOS_ = false;
			} else{
				anyOS_ = true;
			}
		}

		bool ruleAction() const
		{
			if(anyOS_ && osName_ == sysName()){
				return action_;
			}else {
				return reverseAction(action_);
			}
		}
	private:
		Action action_;

		bool anyOS_;

		QString osName_;

	};
	QList<Rule> ruleList_;
};

#endif // RULER_H
