#ifndef NEWGAME_H
#define NEWGAME_H

#include <QObject>
#include <QProcess>

#include "core/GameParser.h"

class Launcher : public QObject
{
	Q_OBJECT
public:
	explicit Launcher(QObject *parent, Profile profile, LaunchAuth auth);

	void start();

	void extractNatives();

signals:
	void finished(int);

public slots:
	void deleteNatives();

private:
	GameParser gameParser_;
	QProcess *gameProcess_;
};

#endif // NEWGAME_H
