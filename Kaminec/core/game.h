#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>
#include <QProcess>

#include "messager/profile.h"
#include "core/Auth.h"
#include "core/jsonmanager.h"
#include "assistance/logger.h"

class Game: public QObject
{
    Q_OBJECT
public:
	Game(QObject *parent, Profile profile, Auth *auth);

    int start();

    QStringList genStartcode();

	QStringList genJVMArgs();
	QStringList genGameArgs();

	QString genLibpath();

	int extractNatives();
private:
	static bool deleteDirectory(const QString &path);

    Profile gameProfile;
	Auth *gameAuth;
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
