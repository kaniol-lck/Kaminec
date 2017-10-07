#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>
#include <QProcess>

#include "profile.h"
#include "gamemode.h"
#include "jsonmanager.h"

class Game: public QObject
{
    Q_OBJECT
public:
	Game(QObject *parent, Profile gp, Mode gm);

    int start();

    QStringList genStartcode();

    QStringList genJVMargs();
    QStringList genLibpath();
	QStringList genGameArgs();

	int extractNatives();
private:
	static bool deleteDirectory(const QString &path);

    Profile gameProfile;
	Mode gameMode;
    JsonManager gameJson;
	QProcess *gameProcess;
	QString corePath;
signals:
    void finished(int);

public slots:
	void deleteNatives();
};

#endif // GAME_H
