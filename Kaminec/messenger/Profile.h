#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QDateTime>

enum class ProfileType { Custom, LatestRelease, LatestSnapshot };

class Profile
{
public:
	explicit Profile(const QString &name = "New Profile",
					 ProfileType type = ProfileType::Custom,
					 const QString &lastVersionId = "",
					 const QString &gameDir = "",
					 QDateTime created = QDateTime(),
					 QDateTime lastUsed = QDateTime());

	QString name() const;
	ProfileType type() const;
	QString lastVersionId() const;
	QString gameDir() const;
	QDateTime created() const;
	QDateTime lastUsed() const;

	void setlastUsed(const QDateTime &lastUsed);

private:
	QString name_;
	ProfileType type_;
	QString lastVersionId_;
	QString gameDir_;
	QDateTime created_;
	QDateTime lastUsed_;

};

#endif // PROFILE_H
