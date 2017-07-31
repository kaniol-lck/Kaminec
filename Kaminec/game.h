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
	Game(QObject *parent, Profile gp, Mode gm, QPair<QString,QString> account, bool autoName);

    int start();

    QStringList genStartcode();

    QStringList genJVMargs();
    QStringList genLibpath();
	QStringList genGameArgs();

    int extractNatives(QString nativesDir);
private:
    Profile gameProfile;
	Mode gameMode;
    JsonManager gameJson;
    QProcess *gameProcess;
	QPair<QString,QString> gameAccount;
	bool mAutoName;
signals:
    void finished(int);

};

#endif // GAME_H
