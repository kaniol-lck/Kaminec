#ifndef GAMECOREJAR_H
#define GAMECOREJAR_H

#include <QVariant>

class GameCoreJar
{
public:
	GameCoreJar(QVariant gameCoreJarVariant);

	QString sha1() const;
	int size() const;
	QUrl url() const;

private:
	QVariant mGameCoreJarVariant;
};

#endif // GAMECOREJAR_H
