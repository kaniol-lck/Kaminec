#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>
#include <QProcess>

#include "core/json/JsonKit.h"
#include "core/auth/LaunchAuth.h"
#include "core/json/JsonManager.h"
#include "messager/profile.h"
#include "assistance/logger.h"

class Game: public QObject
{
    Q_OBJECT
public:
	Game(QObject *parent, Profile profile, LaunchAuth *auth);

    int start();

    QStringList genStartcode();

	QStringList genJVMArgs();
	QStringList genGameArgs();

	QString genLibpath();

	int extractNatives();
private:
	static bool deleteDirectory(const QString &path);

    Profile gameProfile;
	LaunchAuth *gameAuth;
	JsonManager gameJson;
	QProcess *gameProcess;
	QString corePath;
	Logger *gameLogger;
signals:
    void finished(int);

public slots:
	void deleteNatives();
};

#endif // GAME_H
