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

	void initProfiles();

	Profile getProfile(const QString &name);
	QMap<QString, Profile> getProfiles();

	bool containProfile(const QString &name) const;
	bool checkVersion(const QString &version);
	bool addVersion(const QString &version, const QString &gamePath);

	bool insertProfile(const Profile &profile);
	bool removeProfile(const QString &name);
	bool renameProfile(const QString &oldName, const QString &newName);

	void setSelectedProfile(const QString &name);
	QString getSelectedProfileName();

	//temporary method
	void refresh();

private:
	QFile profilesFile_;
	QMap<QString, Profile> profilesMap;
	QJsonObject profilesObject_;
	Custom custom_;
};

#endif // PROFILEMANAGER_H
