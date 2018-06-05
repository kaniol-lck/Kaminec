#ifndef GAMECOREJAR_H
#define GAMECOREJAR_H

#include <QVariant>

class GameCoreJar
{
public:
	GameCoreJar(const QVariant &gameCoreJarVariant, const QString &version);

	QString name() const;
	QString path() const;
	QString sha1() const;
	int size() const;
	QUrl url() const;

private:
	QVariant gameCoreJarVariant_;
	QString version_;
};

#endif // GAMECOREJAR_H
