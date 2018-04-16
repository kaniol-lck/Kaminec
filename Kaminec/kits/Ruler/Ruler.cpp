#include "Ruler.h"

Ruler::Ruler(const QVariant &rule)
{
	for(const auto& ruleVariant: rule.toList()){
		ruleList_ << Rule(ruleVariant);
	}
}

bool Ruler::isAllow()
{
	bool allow = true;
	for(const auto& action : ruleList_){
		if(!action.ruleAction()){
			allow = false;
			break;
		}
	}

	return allow;
}
