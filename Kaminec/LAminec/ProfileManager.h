#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "messenger/profile.h"
#include "assistance/Custom.h"

#include <QObject>
#include <QFile>
#include <QJsonObject>

class ProfileManager : public QObject
{
	Q_OBJECT
public:
	explicit ProfileManager(QObject *parent = nullptr);

	bool initProfiles(const Profile &profile = Profile());

	Profile getProfile(const QString &name);
	QList<Profile> getProfileList();

	bool checkVersion(const QString &version);
	bool addVersion(const QString &version, const QString &gamePath);

	bool insertProfile(const Profile &profile);
	bool removeProfile(const QString &name);
	bool renameProfile(const QString &oldName, const QString &newName);

	void setSelectedProfile(const QString &name);
	Profile getSelectedProfile();

	//temporary method
	void refresh();

private:
	QFile profilesFile_;
	QJsonObject profilesObject_;
	Custom custom_;
};

#endif // PROFILEMANAGER_H
