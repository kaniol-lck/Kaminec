#ifndef PROFILE_H
#define PROFILE_H

#include <QString>


struct Profile
{
    Profile()=default;
	explicit Profile(QString name,
					 QString lastVersionId,
					 QString gameDir);

	QString name_;
	QString lastVersionId_;
	QString gameDir_;

};

#endif // PROFILE_H
