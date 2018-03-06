#include "profilemanager.h"

#include "core/Path.h"
#include "assistance/utility.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSettings>

ProfileManager::ProfileManager(QObject *parent) :
	QObject(parent),
	profilesFile_(Path::corePath() + "/launcher_profiles.json")
{
	if(!profilesFile_.open(QIODevice::ReadOnly | QIODevice::Text))
		throw std::runtime_error(R"("launcher_profiles.json" opened error.)");
	QByteArray bytes = QString::fromLocal8Bit(profilesFile_.readAll()).toUtf8();
	profilesFile_.close();

	if(bytes.size()==0){
		qDebug()<<"No content,auto make.";
		initProfiles();
	} else{
		QJsonParseError ok;
		profilesVariant_ = QJsonDocument::fromJson(bytes,&ok).toVariant();
		if(ok.error != QJsonParseError::NoError)
			throw std::runtime_error((ok.errorString() + R"("launcher_profiles.json" may be crashed.)").toStdString());
	}
}

bool ProfileManager::initProfiles(const Profile &profile)
{
	QJsonObject json
	{
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

	if(!profilesFile_.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;
	QTextStream out(&profilesFile_);
	auto bytes = QJsonDocument(json).toJson();
	profilesVariant_ = json;
	out<<bytes;
	profilesFile_.close();

	return true;
}

Profile ProfileManager::getProfile(const QString &name)
{
	for(const auto& profileVariant : value(profilesVariant_, "profiles").toMap())
		if(value(profileVariant, "name").toString() == name)
			return Profile(value(profileVariant, "name").toString(),
						   value(profileVariant, "lastVersionId").toString(),
						   value(profileVariant, "gameDir").toString());
	return Profile();
}

QList<Profile> ProfileManager::getProfileList()
{
	QList<Profile> profileList;
	for(const auto& profileVariant : value(profilesVariant_, "profiles").toMap())
		profileList<<Profile(value(profileVariant, "name").toString(),
							 value(profileVariant, "lastVersionId").toString(),
							 value(profileVariant, "gameDir").toString());
	return profileList;
}

bool ProfileManager::checkVersion(const QString &version)
{
	//found this version
	for(const auto& profileVariant : value(profilesVariant_, "profiles").toMap())
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
	auto json = profilesVariant_.toJsonObject();

	auto profiles = value(profilesVariant_, "profiles").toJsonObject();

	profiles.insert(profile.name_, QJsonObject{
					{"name", profile.name_},
					{"lastVersionId", profile.lastVersionId_},
					{"gameDir", profile.gameDir_}
				});


	json.insert("profiles", profiles);

	if(!profilesFile_.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;
	QTextStream out(&profilesFile_);
	auto bytes = QJsonDocument(json).toJson();
	profilesVariant_ = json;
	out<<bytes;
	profilesFile_.close();

	return true;
}

bool ProfileManager::renameProfile(const QString &oldName, const QString &newName)
{	
	auto json = profilesVariant_.toJsonObject();

	auto profiles = value(profilesVariant_, "profiles").toJsonObject();

	auto oldProfile = profiles.take(oldName).toObject();
	oldProfile.insert("name", newName);

	profiles.insert(newName, oldProfile);

	if(!profilesFile_.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	json.insert("profiles", profiles);

	if(oldName == QSettings().value("selectedProfile").toString())
		setSelectedProfile(newName);

	QTextStream out(&profilesFile_);
	auto bytes = QJsonDocument(json).toJson();
	profilesVariant_ = json;
	out<<bytes;
	profilesFile_.close();

	return true;
}

bool ProfileManager::setSelectedProfile(const QString &name)
{
	QSettings().setValue("selectedProfile", name);
	return true;
}

Profile ProfileManager::getSelectedProfile()
{
	return getProfile(QSettings().value("selectedProfile").toString());
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
		profilesVariant_ = QJsonDocument::fromJson(bytes,&ok).toVariant();
		if(ok.error != QJsonParseError::NoError)
			throw std::runtime_error((ok.errorString() + R"("launcher_profiles.json" may be crashed.)").toStdString());
	}
}
