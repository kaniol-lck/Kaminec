#include "Ruler.h"


Ruler::Action Ruler::reverseAction(const Ruler::Action &action){
	if(action == Action::Allow)
		return Action::Disallow;
	else
		return Action::Allow;
}

Ruler::Ruler(QVariant rule)
{
	for(const auto& ruleVariant: rule.toList()){
		mRuleList << Rule(ruleVariant);
	}
}

bool Ruler::isAllow()
{
	bool allow = true;
	for(const auto& action : mRuleList){
		if(action.ruleAction() == Disallow){
			allow = false;
			break;
		}
	}

	return allow;
}
