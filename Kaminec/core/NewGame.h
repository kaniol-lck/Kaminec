#ifndef NEWGAME_H
#define NEWGAME_H

#include <QObject>
#include <QProcess>

#include "core/GameJson.h"
#include "core/LaunchAuth.h"
#include "core/GameJson.h"
#include "messager/profile.h"
#include "assistance/logger.h"

class NewGame : public QObject
{
	Q_OBJECT
public:
	explicit NewGame(QObject *parent, Profile profile, LaunchAuth *auth);

	void start();

	QStringList getStartcode();

	QStringList getJVMArguments();
	QStringList getGameArguments();

	QString getClassPaths();

	void extractNatives();

signals:
	void finished(int);

public slots:
	void deleteNatives();

private:
	Profile gameProfile;
	LaunchAuth *launchAuth;
	GameJson gameJson;
	QProcess *gameProcess;
};

#endif // NEWGAME_H
