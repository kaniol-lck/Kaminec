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

};

#endif // PROFILE_H
