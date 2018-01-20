#include "profile.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>

Profile::Profile(QString name,
				 QString lastVersionId,
				 QString gameDir):
	name_(name),
	lastVersionId_(lastVersionId),
	gameDir_(gameDir)
{}
