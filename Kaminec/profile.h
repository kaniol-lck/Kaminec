#ifndef PROFILE_H
#define PROFILE_H

#include <QString>


struct Profile
{
    Profile()=default;
	explicit Profile(QString name,
					 QString lastVersionId,
					 QString gameDir);

	QString mName;
	QString mLastVersionId;
	QString mGameDir;

	static QMap<QString, Profile> fromJson();
	static QString getSelectedProfile();
	static void setSelectedProfile(QString selectedProfile);
	static void saveProfile(const Profile& profile);
	static void newProfile();
};

#endif // PROFILE_H
