#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QProcess>

#include "profile.h"
#include "gamemode.h"
#include "jsonmanager.h"

class game
{
public:
    game()=default;
    explicit game(profile gp,mode gm);
    ~game()=default;

    int start();

    QStringList genStartcode();

    QStringList genJVMargs();
    QStringList genLibpath();
    QStringList genGameargs();
    QStringList checkSession();

    int extractNatives(QString nativesDir);
private:
    profile gameProfile;
    mode gamemode;
    jsonManager gameJson;

};

#endif // GAME_H
