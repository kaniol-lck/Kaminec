#include "GameCoreJar.h"

#include "assistance/utility.h"

#include <QUrl>

GameCoreJar::GameCoreJar(const QVariant &gameCoreJarVariant, const QString &version) :
	gameCoreJarVariant_(gameCoreJarVariant),
	version_(version)
{}

QString GameCoreJar::version() const
{
	return version_;
}

QString GameCoreJar::path() const
{
	return QString("<versions>/%1/%1.jar").arg(version_);
}

QString GameCoreJar::sha1() const
{
	return value(gameCoreJarVariant_, "sha1").toString();
}

int GameCoreJar::size() const
{
	return value(gameCoreJarVariant_, "size").toInt();
}

QUrl GameCoreJar::url() const
{
	return value(gameCoreJarVariant_, "url").toUrl();
}
