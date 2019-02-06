#ifndef PROFILE_H
#define PROFILE_H

#include <QString>


class Profile
{
public:
	explicit Profile(const QString &name = "New Profile",
					 const QString &lastVersionId = "Default",
					 const QString &gameDir = "");

	QString name() const;
	QString lastVersionId() const;
	QString gameDir() const;

private:
	QString name_;
	QString lastVersionId_;
	QString gameDir_;

};

#endif // PROFILE_H
