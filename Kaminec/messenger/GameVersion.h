#ifndef GAMEVERSION_H
#define GAMEVERSION_H

#include <QString>

enum class VersionType{ SnapShot, Release };

class GameVersion
{
public:
	explicit GameVersion(const QString &versionName = "");
	QString versionName() const;

private:
	QString versionName_;
};

#endif // GAMEVERSION_H
