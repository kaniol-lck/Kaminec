#include "Arguments.h"

#include "core/Ruler.h"

Arguments::Arguments(const QString &arguments) :
	//split the arguments with whitespace
	Arguments(arguments.split(" "))
{}

Arguments::Arguments(const QStringList &arguments)
{
	/*1.0.json:
	 *"minecraftArguments":
	 *"${auth_player_name} ${auth_session} --gameDir ${game_directory} --assetsDir ${game_assets}"
	 */

	arguments_ = arguments;

	for(auto i = 0; i != arguments_.size(); i++){
		if(arguments_.at(i).startsWith("--")||
		   optionGroupMark_.isEmpty()||
		   !arguments_.at(optionGroupMark_.last()).startsWith("--")){
			optionGroupMark_.append(i);
		}
	}
}

Arguments::Arguments(const QVariant &arguments)
{
	for(const auto& argument : arguments.toList()){
		if(argument.toMap().contains("rules")){
			Ruler ruler(value(argument, "rules"));
			if(ruler.isAllow()){
				if(value(argument, "value").toString() != "")
					arguments_.append(value(argument, "value").toString());
				else
					arguments_.append(value(argument, "value").toStringList());
			}
		} else
			arguments_.append(argument.toString());
	}
}

void Arguments::replace(const QString &before, const QString &after)
{
	for(auto& argument : arguments_)
		argument.replace(before, after);
}

bool Arguments::setOption(const QString &optionName, const QString &optionContent)
{
	for(auto it = optionGroupMark_.begin(); it != optionGroupMark_.end(); it++){
		//found this option
		if(arguments_.at(*it) == optionName){
			//if this option have only one argument
			if(*it == arguments_.size()-1 ||
			   *it == *(it+1) - 1){
				arguments_.insert(*it, optionContent);
				for(; it != optionGroupMark_.end(); it++)
					*it += 1;
			}
			else
				arguments_.replace(*it+1, optionContent);
			return true;
		}
	}
	//this option is not exist
	return false;
}

void Arguments::addOption(const QString &optionName)
{
	optionGroupMark_.append(arguments_.size()+1);
	arguments_.append(optionName);
}

void Arguments::addOption(const QString &optionName, const QString &optionContent)
{
	addOption(optionName);
	arguments_.append(optionContent);
}

QStringList Arguments::toStringList() const
{
	return arguments_;
}
