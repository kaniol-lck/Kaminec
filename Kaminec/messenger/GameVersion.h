#ifndef GAMEVERSION_H
#define GAMEVERSION_H

#include <QString>
#include <QUrl>

enum class VersionType{ SnapShot, Release };

class GameVersion
{
public:
	explicit GameVersion(const QString &versionName = "",
						 const QUrl &url = QUrl());
	QString versionName() const;
	QUrl url() const;

private:
	QString versionName_;
	QUrl url_;
};

#endif // GAMEVERSION_H
