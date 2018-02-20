#ifndef GAMECOREJAR_H
#define GAMECOREJAR_H

#include <QVariant>

class GameCoreJar
{
public:
	GameCoreJar(const QVariant &gameCoreJarVariant);

	QString sha1() const;
	int size() const;
	QUrl url() const;

private:
	QVariant gameCoreJarVariant_;
};

#endif // GAMECOREJAR_H
