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
	model_.setColumnCount(3);
	model_.setHeaderData(Column::Name, Qt::Horizontal, "name");
	model_.setHeaderData(Column::LastVersionId, Qt::Horizontal, "lastVersionId");
	model_.setHeaderData(Column::GameDir, Qt::Horizontal, "game directroy");

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
		Profile profile(value(it, "name").toString(),
						value(it, "lastVersionId").toString(),
						value(it, "gameDir").toString());
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

bool ProfileManager::insertProfile(const Profile &profile)
{
	model_.appendRow(profile2itemList(profile));
	auto profiles = profilesObject_.value("profiles").toObject();

	profiles.insert(profile.name(), QJsonObject{
						{"name", profile.name()},
						{"lastVersionId", profile.lastVersionId()},
						{"gameDir", profile.gameDir()}
					});
	profilesObject_.insert("profiles", profiles);
	writeToFile();

	if(profilesMap_.isEmpty())
		setSelectedProfileName(profile.name());
	profilesMap_.insert(profile.name(), profile);
	sort(getProfileSorting(), getProfileAscending());
}

bool ProfileManager::removeProfile(const QString &profileName)
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
	auto row = model_.findItems(profileName, Qt::MatchExactly, Column::Name).first()->row();
	model_.removeRow(row);
	profilesMap_.remove(profileName);
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
	auto lastVersionIdItem = new QStandardItem(profile.lastVersionId());
	auto gameDirItem = new QStandardItem(profile.gameDir());
	nameItem->setCheckable(false);
	nameItem->setCheckState(Qt::Unchecked);

	return QList<QStandardItem*>{ nameItem, lastVersionIdItem, gameDirItem };
}

void ProfileManager::sort(const QString &accountSorting, bool accountAscending)
{
	if(accountSorting == "byName")
		model_.sort(Column::Name, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byLastVersionId")
		model_.sort(Column::LastVersionId, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byGameDir")
		model_.sort(Column::GameDir, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
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
}
