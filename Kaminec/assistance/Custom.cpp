#include "Custom.h"

Custom::Custom() :
	settings_("./Kaminec_settings.ini", QSettings::IniFormat)
{}

void Custom::setMemoryAllocateRange(int minimum, int maximum)
{
	settings_.setValue("minMem", minimum);
	settings_.setValue("maxMem", maximum);
}

void Custom::setMemoryAllocateRange(QPair<int, int> range)
{
	setMemoryAllocateRange(range.first, range.second);
}

QPair<int, int> Custom::getMemoryAllocateRange() const
{
	return qMakePair(settings_.value("minMem", 128).toInt(),
					 settings_.value("maxmem", 1024).toInt());
}

void Custom::setJVMArgumentsPolicy(Custom::JVMArgumentsPolicy policy)
{
	settings_.setValue("JVMArgumentsPolicy", static_cast<int>(policy));
}

Custom::JVMArgumentsPolicy Custom::getJVMArgumentsPolicy()
{
	return static_cast<JVMArgumentsPolicy>(settings_.value("JVMArgumentsPolicy", 0).toInt());
}

void Custom::setCustomJVMArguments(QStringList arguments)
{
	settings_.setValue("customJVMArguments", arguments.join("\\n"));
}


QStringList Custom::getCustomJVMArguments() const
{
	return settings_.value("customJVMArguments").toString().split("\\n");
}

void Custom::setLanguage(QString &language)
{
	settings_.setValue("language", language);
}

QString Custom::getLanguage() const
{
	auto index = languages_code.indexOf(QLocale().country());
	if(index == -1) index = 0;
	return settings_.value("language", languages.at(index)).toString();
}

void Custom::setGameWindowSize(int width, int height)
{
	settings_.setValue("GameWindowWidth", width);
	settings_.setValue("GameWindowHeight", height);
}

void Custom::setGameWindowSize(QPair<int, int> size)
{
	setGameWindowSize(size.first, size.second);
}

QPair<int, int> Custom::getGameWindowSize() const
{
	return qMakePair(settings_.value("GameWindowWidth", 854).toInt(),
					 settings_.value("GameWindowHeight", 480).toInt());
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
