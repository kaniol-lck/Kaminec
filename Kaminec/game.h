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
    Game(QObject *parent,Profile gp,Mode gm);

    int start();

    QStringList genStartcode();

    QStringList genJVMargs();
    QStringList genLibpath();
    QStringList genGameargs();
    QStringList checkSession();

    int extractNatives(QString nativesDir);
private:
    Profile gameProfile;
    Mode gamemode;
    JsonManager gameJson;
    QProcess *gameProcess;
signals:
    void finished(int);

};

#endif // GAME_H
