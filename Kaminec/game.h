#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>
#include <QProcess>

#include "profile.h"
#include "gamemode.h"
#include "jsonmanager.h"

class game: public QObject
{
    Q_OBJECT
public:
    game(QObject *parent,profile gp,mode gm);

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

signals:
    void finished(int);

};

#endif // GAME_H
