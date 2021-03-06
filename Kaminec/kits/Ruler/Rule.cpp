#include "Rule.h"

#include "assistance/utility.h"
#include "assistance/systeminfo.h"
#include "assistance/Custom.h"

Rule::Rule(const QVariant &rule)
{
	if(value(rule, "action").toString() == "allow"){
		action_ = ALLOW;
	} else{
		action_ = DISALLOW;
	}

	//os infomation check
	if(rule.toMap().contains("os"))
		if(value(rule, "os", "name").toString() != sysName())
			action_ = !action_;

	//features infomation check
	if(rule.toMap().contains("features")){
		auto featuresMap = value(rule, "features").toMap();
		for(auto it = featuresMap.begin(); it != featuresMap.end(); it++){
			if(checkFeature(it.key()) != it.value().toBool())
				action_ = false;
		}
	}
}

Rule::Action Rule::ruleAction() const
{
	return action_;
}

bool Rule::checkFeature(const QString &key)
{
	if(key == "has_custom_resolution")
		return Custom().getCustomizeResolution() &&
				!Custom().getFullScreen();
	return false;
}
