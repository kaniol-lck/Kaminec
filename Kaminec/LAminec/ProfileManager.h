#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "messager/profile.h"

#include <QObject>
#include <QFile>
#include <QVariant>

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

	bool setSelectedProfile(const QString &name);
	Profile getSelectedProfile();

	//temporary method
	void refresh();

private:
	QFile profilesFile_;
	QVariant profilesVariant_;

};

#endif // PROFILEMANAGER_H
