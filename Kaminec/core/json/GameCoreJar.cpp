#include "GameCoreJar.h"

#include "assistance/utility.h"

#include <QUrl>

GameCoreJar::GameCoreJar(QVariant gameCoreJarVariant) :
	gameCoreJarVariant_(gameCoreJarVariant)
{}

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
