#include "GameCoreJar.h"

#include "assistance/utility.h"

#include <QUrl>

GameCoreJar::GameCoreJar(QVariant gameCoreJarVariant) :
	gameCoreJarVariant_(gameCoreJarVariant)
{}

QString GameCoreJar::sha1() const
{
	static QString mSha1 = value(gameCoreJarVariant_, "sha1").toString();
	return mSha1;
}

int GameCoreJar::size() const
{
	static int mSize = value(gameCoreJarVariant_, "size").toInt();
	return mSize;
}

QUrl GameCoreJar::url() const
{
	static QUrl mUrl = value(gameCoreJarVariant_, "url").toUrl();
	return mUrl;
}
