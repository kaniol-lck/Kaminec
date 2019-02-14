#include "profilemanager.h"

#include "assistance/PathReplacer.h"
#include "assistance/utility.h"
#include "exception/Exceptions.hpp"
#include "messenger/GameVersion.h"

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
	model_.setColumnCount(5);
	model_.setHeaderData(Column::Name, Qt::Horizontal, "name");
	model_.setHeaderData(Column::LastVersionId, Qt::Horizontal, "lastVersionId");
	model_.setHeaderData(Column::GameDir, Qt::Horizontal, "game directroy");
	model_.setHeaderData(Column::Created, Qt::Horizontal, "created");
	model_.setHeaderData(Column::LastUsed, Qt::Horizontal, "lastUsed");

	if(!profilesFile_.open(QIODevice::ReadWrite | QIODevice::Text))
		throw FileOpenException(profilesFile_.fileName());

	QByteArray bytes = QString::fromLocal8Bit(profilesFile_.readAll()).toUtf8();
	profilesFile_.close();

	if(bytes.isEmpty()){
		qDebug()<<"No content,auto make.";
		initProfiles();
		return;
	}

	QJsonParseError ok;
	profilesObject_ = QJsonDocument::fromJson(bytes,&ok).object();
	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(profilesFile_.fileName(), ok.errorString(), true);

	auto profilesVariant = profilesObject_.value("profiles").toVariant();
	for(auto it : profilesVariant.toMap()){
		auto typeStr = value(it, "type").toString();
		ProfileType type;
		if(typeStr == "custom")
			type = ProfileType::Custom;
		else if(typeStr == "latest-release")
			type = ProfileType::LatestRelease;
		else if(typeStr == "latest-snapshot")
			type = ProfileType::LatestSnapshot;

		Profile profile(value(it, "name").toString(),
						type,
						GameVersion(value(it, "lastVersionId").toString()),
						value(it, "gameDir").toString(),
						QDateTime::fromString(value(it, "created").toString(), Qt::ISODateWithMs),
						QDateTime::fromString(value(it, "lastUsed").toString(), Qt::ISODateWithMs));
		if(!profile.name().isEmpty()){
			profilesMap_.insert(profile.name(), profile);
			model_.appendRow(profile2itemList(profile));
		}
	}

	sort(getProfileSorting(), getProfileAscending());

	auto items = model_.findItems(getSelectedProfileName(), Qt::MatchExactly, Column::Name);
	if(!items.isEmpty())
		model_.item(items.first()->row(), Column::Name)->setCheckState(Qt::Checked);//set check state
}

QStandardItemModel *ProfileManager::getProfilesModel()
{
	return &model_;
}

void ProfileManager::initProfiles()
{
	Profile profile;
	insertProfile(profile);
	setProfileSorting("ByName");
	setProfileAscending(true);
}

Profile ProfileManager::getProfile(const QString &name) const
{
	return profilesMap_.value(name);
}

QMap<QString, Profile> ProfileManager::getProfiles() const
{
	return profilesMap_;
}

bool ProfileManager::containProfile(const QString &name) const
{
	return profilesMap_.contains(name);
}

void ProfileManager::insertProfile(const Profile &profile)
{
	model_.appendRow(profile2itemList(profile));
	auto profiles = profilesObject_.value("profiles").toObject();
	profiles.insert(profile.name(), profile2object(profile));
	profilesObject_.insert("profiles", profiles);
	writeToFile();

	if(profilesMap_.isEmpty())
		setSelectedProfileName(profile.name());
	profilesMap_.insert(profile.name(), profile);
	sort(getProfileSorting(), getProfileAscending());
}

void ProfileManager::removeProfile(const QString &profileName)
{
	//if the profile to be removed is selected, set the first in remains as the selected
	if(getSelectedProfileName() == profileName && profilesMap_.count() > 1){
		auto items = model_.findItems(profileName, Qt::MatchExactly, Column::Name);
		if(!items.isEmpty()){
			auto row = items.first()->row()==1?2:1;
			model_.item(row, Column::Name)->setCheckState(Qt::Checked);
			profilesObject_.insert("selectedprofileName", model_.item(row, Column::Name)->data(Qt::DisplayRole).toString());
			writeToFile();
		}
	}

	QJsonObject profiles = profilesObject_.value("profiles").toObject();
	profiles.remove(profileName);
	profilesObject_.insert("profiles", profiles);
	writeToFile();
	model_.removeRow(model_.findItems(profileName, Qt::MatchExactly, Column::Name).first()->row());
	profilesMap_.remove(profileName);
}

void ProfileManager::editProfile(const QString &oldProfileName, Profile newProfile)
{
	auto oldProfile = profilesMap_.take(oldProfileName);
	newProfile.setLastUsed(oldProfile.created());
	profilesMap_.insert(newProfile.name(), newProfile);

	if(profilesObject_.value("selectedProfileName").toString() == oldProfileName)
		profilesObject_.insert("selectedprofileName", newProfile.name());
	QJsonObject profiles = profilesObject_.value("profiles").toObject();
	profiles.remove(oldProfileName);
	profiles.insert(newProfile.name(), profile2object(newProfile));
	profilesObject_.insert("profiles", profiles);
	writeToFile();

	model_.removeRow(model_.findItems(oldProfileName, Qt::MatchExactly, Column::Name).first()->row());
	model_.appendRow(profile2itemList(newProfile));
}

void ProfileManager::setSelectedProfileName(const QString &profileName)
{
	auto oldProfileName = getSelectedProfileName();
	profilesObject_.insert("selectedProfileName", QJsonValue(profileName));

	writeToFile();

	auto items = model_.findItems(oldProfileName, Qt::MatchExactly, Column::Name);
	if(!items.isEmpty())
		model_.item(items.first()->row(), Column::Name)->setCheckState(Qt::Unchecked);//remove check state

	items = model_.findItems(profileName, Qt::MatchExactly, Column::Name);
	if(!items.isEmpty())
		model_.item(items.first()->row(), Column::Name)->setCheckState(Qt::Checked);//set check state
}

QString ProfileManager::getSelectedProfileName()
{
	if(!profilesObject_.contains("selectedProfileName")) return "";
	auto selectedprofileName = profilesObject_.value("selectedProfileName").toString();
	if(!profilesMap_.contains(selectedprofileName) && model_.rowCount() != 0){
		selectedprofileName = nameFromIndex(model_.index(0,0));
		profilesObject_.insert("selectedProfileName", QJsonValue(selectedprofileName));
		writeToFile();//set the first profile as selected
	}
	return selectedprofileName;
}

void ProfileManager::setProfileSorting(QString profileSorting)
{
	auto settings = profilesObject_.value("settings").toObject();
	settings.insert("profileSorting", profileSorting);
	profilesObject_.insert("settings", settings);

	writeToFile();
}

QString ProfileManager::getProfileSorting() const
{
	return profilesObject_.value("settings").toObject().value("profileAscending").toString();
}

void ProfileManager::setProfileAscending(bool profileAscending)
{
	auto settings = profilesObject_.value("settings").toObject();
	settings.insert("profileAscending", profileAscending);
	profilesObject_.insert("settings", settings);

	writeToFile();
}

bool ProfileManager::getProfileAscending() const
{
	return profilesObject_.value("settings").toObject().value("profileAscending").toBool();
}

QString ProfileManager::nameFromIndex(const QModelIndex &index) const
{
	return model_.item(index.row(), Column::Name)->data(Qt::DisplayRole).toString();
}

QList<QStandardItem *> ProfileManager::profile2itemList(const Profile &profile)
{
	auto nameItem = new QStandardItem(profile.name());
	auto lastVersionIdItem = new QStandardItem(profile.lastVersionId().versionName());
	auto gameDirItem = new QStandardItem(profile.gameDir());
	auto createdItem = new QStandardItem(profile.created().toString(Qt::ISODateWithMs));
	auto lastUsedItem = new QStandardItem(profile.lastUsed().toString(Qt::ISODateWithMs));
	nameItem->setCheckable(false);
	nameItem->setCheckState(Qt::Unchecked);

	return QList<QStandardItem*>{ nameItem, lastVersionIdItem, gameDirItem, createdItem, lastUsedItem };
}

QJsonObject ProfileManager::profile2object(const Profile &profile)
{
	if(profile.type() == ProfileType::Custom)
		return QJsonObject{
			{"name", profile.name()},
			{"type", "custom"},
			{"lastVersionId", profile.lastVersionId().versionName()},
			{"gameDir", profile.gameDir()},
			{"created", profile.created().toString(Qt::ISODateWithMs)},
			{"lastUsed", profile.lastUsed().toString(Qt::ISODateWithMs)}
		};
	else
		return QJsonObject{
			{"name", profile.name()},
			{"type", profile.type() == ProfileType::LatestRelease?"latest-release":"latest-snapshot"},
			{"gameDir", profile.gameDir()},
			{"created", profile.created().toString(Qt::ISODateWithMs)},
			{"lastUsed", profile.lastUsed().toString(Qt::ISODateWithMs)}
		};
}

void ProfileManager::sort(const QString &accountSorting, bool accountAscending)
{
	if(accountSorting == "byName")
		model_.sort(Column::Name, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byLastVersionId")
		model_.sort(Column::LastVersionId, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byGameDir")
		model_.sort(Column::GameDir, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byCreated")
		model_.sort(Column::Created, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byLastUsed")
		model_.sort(Column::LastUsed, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
}

void ProfileManager::fixProfiles(QList<GameVersion> gameVersions)
{
	QStringList homelessVersionNames;
	for(auto gameVersion : gameVersions)
		homelessVersionNames << gameVersion.versionName();
	for(auto profile : getProfiles()){
		auto index = homelessVersionNames.indexOf(profile.lastVersionId().versionName());
		if(index != 1)
			homelessVersionNames.removeAt(index);
	}
	for(auto homelessVersionName : homelessVersionNames){
		insertProfile(Profile(homelessVersionName, ProfileType::Custom, GameVersion(homelessVersionName)));
	}
}

void ProfileManager::writeToFile()
{
	if(!profilesFile_.open(QIODevice::WriteOnly | QIODevice::Text))
		throw FileOpenException(profilesFile_.fileName());
	QTextStream out(&profilesFile_);
	auto bytes = QJsonDocument(profilesObject_).toJson();
	out<<bytes;
	profilesFile_.close();
}

void ProfileManager::sortRecord(int column)
{
	if(column == Column::Name)
		setProfileSorting("byName");
	else if(column == Column::LastVersionId)
		setProfileSorting("byLastVersionId");
	else if(column == Column::GameDir)
		setProfileSorting("byGameDir");
	else if(column == Column::Created)
		setProfileSorting("byCreated");
	else if(column == Column::LastUsed)
		setProfileSorting("byLastUsed");
}
