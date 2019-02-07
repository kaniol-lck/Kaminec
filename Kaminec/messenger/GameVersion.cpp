#include "GameVersion.h"

GameVersion::GameVersion(const QString &versionName) :
	versionName_(versionName)
{}

QString GameVersion::versionName() const
{
	return versionName_;
}
