#include "profilemanager.h"
#include "messager/profile.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDebug>

ProfileManager::ProfileManager(QObject *parent) : QObject(parent)
{
	QString corePath = QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).toString();
	if(!QDir(corePath).exists()){
		QDir().mkpath(corePath);
	}
	QFile loadfile(corePath + "/launcher_profiles.json");

	if(!loadfile.open(QIODevice::ReadWrite|QIODevice::Text)){
		qDebug()<<R"("launcher_profiles.json" opened error.)";
	}

	QByteArray bytes = QString::fromLocal8Bit(loadfile.readAll()).toUtf8();
	if(bytes.size()==0){
		qDebug()<<"No content,auto make.";
		QJsonObject json;
		json.insert("selectedProfile","(Default)");
		QJsonObject profiles;
		QJsonObject profile;
		profile.insert("name","(Default)");
		profile.insert("lastVersionId","1.10.2");
		profile.insert("gameDir",QSettings().value("corePath").toString());
		profiles.insert("(Default)",profile);
		json.insert("profiles",profiles);

		QTextStream out(&loadfile);
		bytes = QJsonDocument(json).toJson();
		out<<bytes;
	}
	loadfile.close();

	QJsonParseError ok;
	profilesMgrObj = QJsonDocument::fromJson(bytes,&ok).object();
	if(ok.error != QJsonParseError::NoError){
		qDebug()<<ok.errorString();
		qDebug()<<R"("launcher_profiles.json" may be crashed.)";
	}
}

bool ProfileManager::checkVersion(QString version)
{
	return profilesMgrObj.value("profiles").toVariant().toMap().contains("auto-version-" + version);
}

void ProfileManager::addVersion(QString version, QString gamePath)
{
	QString corePath = QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).toString();
	QFile loadfile(corePath + "/launcher_profiles.json");

	QJsonObject profile;
	QJsonObject profiles = profilesMgrObj.value("profiles").toObject();

	profile.insert("name","auto-version-" + version);
	profile.insert("lastVersionId", version);
	profile.insert("gameDir", gamePath);

	profiles.insert("auto-version-" + version, profile);
	profilesMgrObj.insert("profiles", profiles);

	if(!loadfile.open(QIODevice::ReadWrite|QIODevice::Text)){
		qDebug()<<R"("launcher_profiles.json" opened error.)";
	}

	QTextStream out(&loadfile);
	auto bytes = QJsonDocument(profilesMgrObj).toJson();
	out<<bytes;
}
