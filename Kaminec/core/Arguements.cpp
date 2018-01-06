#include "Arguements.h"

Arguements::Arguements(QString arguements)
{
	//split the arguements with whitespace
	auto arguementList = arguements.split(" ");

	for(const QString& arguement : arguementList){
		if(arguement.startsWith("--"))
			options << QStringList{ arguement };
		else
			options.last().append(arguement);
	}

}

void Arguements::replace(const QString &before, const QString &after)
{
	for(auto& option : options)
		for(auto& item : option)
			item.replace(before, after);
}

bool Arguements::setOption(const QString &optionName, const QString &optionContent)
{
	for(auto& option : options){
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

void Arguements::addOption(const QString &optionName)
{
	options << QStringList{ optionName };
}

void Arguements::addOption(const QString &optionName, const QString &optionContent)
{
	options << QStringList{ optionName, optionContent};
}

QStringList Arguements::toStringList() const
{
	QStringList arguementList;
	for(const auto& option : options)
		arguementList << option;
	return arguementList;
}
