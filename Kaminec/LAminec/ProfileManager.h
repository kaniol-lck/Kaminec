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

	QList<Profile> getProfileList();

	bool checkVersion(const QString &version);
	bool addVersion(const QString &version, const QString &gamePath);

	void addProfile(const QString &name, const QString &version, const QString &gamePath);

	bool setSelectedProfile(const QString &name);
	Profile getSelectedProfile();

private:
	QFile profilesFile_;
	QVariant profilesVariant_;

};

#endif // PROFILEMANAGER_H
