#include "profilemanager.h"

#include "core/Path.h"
#include "assistance/utility.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QDebug>

ProfileManager::ProfileManager(QObject *parent) :
	QObject(parent),
	profilesFile_(Path::corePath() + "/launcher_profiles.json")
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
	} else{
		QJsonParseError ok;
		profilesObject_ = QJsonDocument::fromJson(bytes,&ok).object();
		if(ok.error != QJsonParseError::NoError)
			throw std::runtime_error((ok.errorString() + R"("launcher_profiles.json" may be crashed.)").toStdString());
	}
}

bool ProfileManager::initProfiles(const Profile &profile)
{
	profilesObject_ = QJsonObject{
		{"profiles", QJsonObject{
				{profile.name_, QJsonObject{
						{"name", profile.name_},
						{"lastVersionId", profile.lastVersionId_},
						{"gameDir", profile.gameDir_}
					}
				}
			}
		}
	};

	if(!profilesFile_.open(QIODevice::WriteOnly | QIODevice::Text))return false;
	QTextStream out(&profilesFile_);
	auto bytes = QJsonDocument(profilesObject_).toJson();
	out<<bytes;
	profilesFile_.close();

	return true;
}

Profile ProfileManager::getProfile(const QString &name)
{
	for(const auto& profileVariant : profilesObject_.value("profiles").toVariant().toMap())
		if(value(profileVariant, "name").toString() == name)
			return Profile(value(profileVariant, "name").toString(),
						   value(profileVariant, "lastVersionId").toString(),
						   value(profileVariant, "gameDir").toString());
	return Profile();
}

QList<Profile> ProfileManager::getProfileList()
{
	QList<Profile> profileList;
	for(const auto& profileVariant : profilesObject_.value("profiles").toVariant().toMap()){
		profileList<<Profile(value(profileVariant, "name").toString(),
							 value(profileVariant, "lastVersionId").toString(),
							 value(profileVariant, "gameDir").toString());
	}
	return profileList;
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

	profiles.insert(profile.name_, QJsonObject{
					{"name", profile.name_},
					{"lastVersionId", profile.lastVersionId_},
					{"gameDir", profile.gameDir_}
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

bool ProfileManager::setSelectedProfile(const QString &name)
{
	custom_.setSelectedProfileName(name);
	return true;
}

Profile ProfileManager::getSelectedProfile()
{
	return getProfile(custom_.getSelectedProfileName());
}

void ProfileManager::refresh()
{
	profilesFile_.setFileName(Path::corePath() + "/launcher_profiles.json");
	if(!profilesFile_.open(QIODevice::ReadOnly | QIODevice::Text))
		throw std::runtime_error(R"("launcher_profiles.json" opened error.)");
	QByteArray bytes = QString::fromLocal8Bit(profilesFile_.readAll()).toUtf8();
	profilesFile_.close();

	if(bytes.size()==0){
		qDebug()<<"No content,auto make.";
		initProfiles();
	} else{
		QJsonParseError ok;
		profilesObject_ = QJsonDocument::fromJson(bytes,&ok).object();
		if(ok.error != QJsonParseError::NoError)
			throw std::runtime_error((ok.errorString() + R"("launcher_profiles.json" may be crashed.)").toStdString());
	}
}
