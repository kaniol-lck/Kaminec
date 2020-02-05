#ifndef PROFILE_H
#define PROFILE_H

#include "messenger/GameVersion.h"

#include <QDateTime>

enum class ProfileType { Custom, LatestRelease, LatestSnapshot };

class Profile
{
public:
	explicit Profile(const QString &name = "New Profile",
					 ProfileType type = ProfileType::Custom,
					 const GameVersion &lastVersionId = GameVersion(""),
                     const QString &gameDir = "",
					 QDateTime created = QDateTime::currentDateTime(),
					 QDateTime lastUsed = QDateTime());

	QString name() const;
	ProfileType type() const;
	GameVersion lastVersionId() const;
	QString gameDir() const;
	QDateTime created() const;
	QDateTime lastUsed() const;

	void setLastUsed(const QDateTime &lastUsed);

private:
	QString name_;
	ProfileType type_;
	GameVersion lastVersionId_;
	QString gameDir_;
	QDateTime created_;
	QDateTime lastUsed_;

};

#endif // PROFILE_H
