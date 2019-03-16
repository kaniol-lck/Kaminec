#include "GameVersion.h"

GameVersion::GameVersion(const QString &versionName, const QUrl &url) :
	versionName_(versionName),
	url_(url)
{}

QString GameVersion::versionName() const
{
	return versionName_;
}

QUrl GameVersion::url() const
{
	return  url_;
}
