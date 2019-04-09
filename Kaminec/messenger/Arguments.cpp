#include "Arguments.h"

#include "kits/Ruler/Ruler.h"
#include "assistance/utility.h"

#include <QString>

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

	for(QString argument : arguments){
		if(argument.startsWith("--") || argument.isEmpty() ||
		   !arguments_.last().first().startsWith("--")){
			arguments_.append(QStringList(argument));
		} else{
			arguments_.last().append(argument);
		}
	}
}

void Arguments::replace(const QString &before, const QString &after)
{
	for(auto& option : arguments_)
		for(auto& argument : option)
			argument.replace(before, after);
}

void Arguments::setOption(const QString &optionName, const QString &optionContent)
{
	for(auto &option : arguments_)
		if(option.first() == optionName){
			option[1] = optionContent;
			return;
		}
	arguments_.append(QStringList{optionName, optionContent});
}

void Arguments::setOption(const QString &optionName)
{
	for(const auto &option : arguments_)
		if(option.first() == optionName)
			return;
	arguments_.append(QStringList{optionName});
}

void Arguments::append(Arguments arguments)
{
	arguments_.append(arguments.arguments_);
}

QStringList Arguments::toStringList() const
{
	QStringList list;
	for(const auto &option : arguments_)
		list << option;
	return list;
}

QString Arguments::toString() const
{
	QStringList list;
	for(const auto &option : arguments_)
		list << option.join(" ");
	return list.join("\n");
}

Arguments Arguments::fromVariant(const QVariant &argumentsVariant)
{
	QStringList arguments;
	for(const auto& argument : argumentsVariant.toList()){
		if(argument.toMap().contains("rules")){
			Ruler ruler(value(argument, "rules"));
			if(ruler.isAllow()){
				if(value(argument, "value").toString() != "")
					arguments.append(value(argument, "value").toStringList());
				else
					arguments.append(value(argument, "value").toStringList());
			}
		} else
			arguments.append(argument.toStringList());
	}
	return Arguments(arguments);
}
