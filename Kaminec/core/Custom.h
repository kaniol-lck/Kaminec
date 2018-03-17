#ifndef CUSTOM_H
#define CUSTOM_H

#include <QSettings>

class Custom
{
public:
	Custom();

	bool checkSettings(QString settingsName);

private:
	QSettings settings_;
};

#endif // CUSTOM_H
