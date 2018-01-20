#include "Arguments.h"

Arguments::Arguments(QString arguments)
{
	//split the arguments with whitespace
	auto argumentList = arguments.split(" ");

	for(const QString& argument : argumentList){
		if(argument.startsWith("--"))
			options_ << QStringList{ argument };
		else
			options_.last().append(argument);
	}

}

void Arguments::replace(const QString &before, const QString &after)
{
	for(auto& option : options_)
		for(auto& item : option)
			item.replace(before, after);
}

bool Arguments::setOption(const QString &optionName, const QString &optionContent)
{
	for(auto& option : options_){
		if(option.first() == optionName){
			if(option.size() == 1)
				option.append(optionContent);
			else
				option.last() = optionContent;
			return true;
		}
	}
	//this option is not exist
	return false;
}

void Arguments::addOption(const QString &optionName)
{
	options_ << QStringList{ optionName };
}

void Arguments::addOption(const QString &optionName, const QString &optionContent)
{
	options_ << QStringList{ optionName, optionContent};
}

QStringList Arguments::toStringList() const
{
	QStringList argumentList;
	for(const auto& option : options_)
		argumentList << option;
	return argumentList;
}
