#include "Arguments.h"

#include "kits/Ruler/Ruler.h"

#include <QString>
#include <QDebug>

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

Arguments::Arguments(const QVariant &arguments)
{
	for(const auto& argument : arguments.toList()){
		if(argument.toMap().contains("rules")){
			Ruler ruler(value(argument, "rules"));
			if(ruler.isAllow()){
				if(value(argument, "value").toString() != "")
					arguments_.append(value(argument, "value").toStringList());
				else
					arguments_.append(value(argument, "value").toStringList());
			}
		} else
			arguments_.append(argument.toStringList());
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
	for(auto option : arguments_)
		if(option.first() == optionName){
			option[1] = optionContent;
			return;
		}
	arguments_.append(QStringList{optionName, optionContent});
}

void Arguments::setOption(const QString &optionName)
{
	for(auto option : arguments_)
		if(option.first() == optionName)
			return;
	arguments_.append(QStringList{optionName});
}

QStringList Arguments::toStringList() const
{
	QStringList list;
	for(auto option : arguments_)
		list << option;
	return list;
}

QString Arguments::toString() const
{
	QStringList list;
	for(auto option : arguments_){
		qDebug()<<option;
		list << option.join(" ");
	}
	return list.join("\n");
}
