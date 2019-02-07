#include "profilemanager.h"

#include "assistance/PathReplacer.h"
#include "assistance/utility.h"
#include "exception/Exceptions.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QDebug>

ProfileManager::ProfileManager(QObject *parent) :
	QObject(parent),
	profilesFile_(PathReplacer::replace("<core>/launcher_profiles.json"))
{
	if(!profilesFile_.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug()<<"No content,auto make.";
		initProfiles();
	}
	QByteArray bytes = QString::fromLocal8Bit(profilesFile_.readAll()).toUtf8();
	profilesFile_.close();

	if(bytes.size()==0){
		qDebug()<<"No content,auto make.";
		initProfiles();
		return;
	}

	QJsonParseError ok;
	profilesObject_ = QJsonDocument::fromJson(bytes,&ok).object();
	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(profilesFile_.fileName(), ok.errorString(), true);

	auto map = profilesObject_.value("profiles").toVariant().toMap();
	for(auto it = map.begin(); it != map.end(); it++){
		if(value(it.value(), "type").toString() == "custom"){
			Profile profile(value(it.value(), "name").toString(),
							value(it.value(), "lastVersionId").toString(),
							value(it.value(), "gameDir").toString());
			profilesMap.insert(it.key(), profile);
		}
	}
}

void ProfileManager::initProfiles()
{
	insertProfile(Profile("Default", "Default", "Default"));
}

Profile ProfileManager::getProfile(const QString &name)
{
	for(auto profile : profilesMap)
		if(profile.name() == name){
			return profile;
		}
	return Profile();
}

QMap<QString, Profile> ProfileManager::getProfiles()
{
	return profilesMap;
}

bool ProfileManager::containProfile(const QString &name) const
{
	bool isContain = false;

	for(auto profile : profilesMap)
		if(profile.name() == name){
			isContain = true;
		}
	return isContain;
}

bool ProfileManager::checkVersion(const QString &version)
{
	//found this version
	for(const auto& profileVariant : profilesObject_.value("profiles").toVariant().toMap())
		if(value(profileVariant, "lastVersionId") == version)
			return true;
	return false;
}

bool ProfileManager::addVersion(const QString &version, const QString &gamePath)
{
	return insertProfile(Profile(version, version, gamePath));
}

bool ProfileManager::insertProfile(const Profile &profile)
{
	auto profiles = profilesObject_.value("profiles").toObject();

	profiles.insert(profile.name(), QJsonObject{
					{"name", profile.name()},
					{"lastVersionId", profile.lastVersionId()},
					{"gameDir", profile.gameDir()}
				});

	profilesObject_.insert("profiles", profiles);

	if(!profilesFile_.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
	QTextStream out(&profilesFile_);
	auto bytes = QJsonDocument(profilesObject_).toJson();
	out<<bytes;
	profilesFile_.close();

	return true;
}

bool ProfileManager::removeProfile(const QString &name)
{
	QJsonObject profiles = profilesObject_.value("profiles").toObject();

	profiles.remove(name);

	profilesObject_.insert("profiles", profiles);

	if(!profilesFile_.open(QIODevice::WriteOnly | QIODevice::Text))return false;
	QTextStream out(&profilesFile_);
	auto bytes = QJsonDocument(profilesObject_).toJson();
	out<<bytes;
	profilesFile_.close();

	return true;
}

bool ProfileManager::renameProfile(const QString &oldName, const QString &newName)
{
	QJsonObject profiles = profilesObject_.value("profiles").toObject();

	auto oldProfile = profiles.take(oldName).toObject();
	oldProfile.insert("name", newName);

	profiles.insert(newName, oldProfile);

	profilesObject_.insert("profiles", profiles);

	if(oldName == custom_.getSelectedProfileName())
		setSelectedProfile(newName);

	if(!profilesFile_.open(QIODevice::WriteOnly | QIODevice::Text))return false;
	QTextStream out(&profilesFile_);
	auto bytes = QJsonDocument(profilesObject_).toJson();
	out<<bytes;
	profilesFile_.close();

	return true;
}

void ProfileManager::setSelectedProfile(const QString &name)
{
	custom_.setSelectedProfileName(name);
}

QString ProfileManager::getSelectedProfileName()
{
	return custom_.getSelectedProfileName();
}

void ProfileManager::refresh()
{
	profilesFile_.setFileName(PathReplacer::replace("<core>/launcher_profiles.json"));
	if(!profilesFile_.open(QIODevice::ReadOnly | QIODevice::Text))
		throw FileOpenException(profilesFile_.fileName());
	QByteArray bytes = QString::fromLocal8Bit(profilesFile_.readAll()).toUtf8();
	profilesFile_.close();

	if(bytes.size()==0){
		qDebug()<<"No content,auto make.";
		initProfiles();
	} else{
		QJsonParseError ok;
		profilesObject_ = QJsonDocument::fromJson(bytes,&ok).object();
		if(ok.error != QJsonParseError::NoError)
			throw JsonParseException(profilesFile_.fileName(), ok.errorString(), true);
	}
}
