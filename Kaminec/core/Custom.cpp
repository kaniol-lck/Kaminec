#include "Custom.h"

Custom::Custom()
{

}

bool Custom::checkSettings(QString settingsName)
{
	return settings_.value(settingsName, false).toBool();
}
