#include "GameCoreJar.h"

#include "assistance/utility.h"

#include <QUrl>

GameCoreJar::GameCoreJar(QVariant gameCoreJarVariant) :
	mGameCoreJarVariant(gameCoreJarVariant)
{}

QString GameCoreJar::sha1() const
{
	static QString mSha1 = value(mGameCoreJarVariant, "sha1").toString();
	return mSha1;
}

int GameCoreJar::size() const
{
	static int mSize = value(mGameCoreJarVariant, "size").toInt();
	return mSize;
}

QUrl GameCoreJar::url() const
{
	static QUrl mUrl = value(mGameCoreJarVariant, "url").toUrl();
	return mUrl;
}
