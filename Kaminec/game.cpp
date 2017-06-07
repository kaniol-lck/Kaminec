#include "game.h"

#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <algorithm>

game::game(profile gp, mode gm):
    gameProfile(gp),
    gamemode(gm),
    gameJson(gameProfile.gameDir
             +QString("/versions/%1/%1.json")
             .arg(gameProfile.version))
{}

int game::start()
{
    //auto gameProcess = new QProcess;
    auto startcode = this->genStartcode();

    qDebug()<<"java="<<gameProfile.javaDir<<endl
           <<"args="<<startcode;

    QFile f("J:/库/桌面/argss.txt");
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return 0;
    QTextStream out(&f);
    for(auto& i:startcode)
        out<<i<<" ";

    auto gameProcess = new QProcess;
    gameProcess->start(
                "\""+gameProfile.javaDir+"\"",
                startcode);
    return 0;
}

QStringList game::genStartcode()
{
    QStringList startcode;
    startcode<<this->genJVMargs()
             <<this->genLibpath()
             <<this->genGameargs()
            //<<this->checkSession()
            ;
    return startcode;
}

QStringList game::genJVMargs()
{
    return QStringList
    {
        "-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump",
        "-XX:+UseG1GC",
        "-XX:-UseAdaptiveSizePolicy",
        "-XX:-OmitStackTraceInFastThrow",
        QString("-Xmn%1m").arg(gameProfile.minMem),
        QString("-Xmx%1m").arg(gameProfile.maxMem),
        "-Dfml.ignoreInvalidMinecraftCertificates=true",
        "-Dfml.ignorePatchDiscrepancies=true"
    };
}


QStringList game::genLibpath()
{
    QStringList libargs;

    QString nativesPath=gameProfile.gameDir+"/natives";//待改
    this->extractNatives(nativesPath);
    libargs<<"-Djava.library.path="+nativesPath;

    auto libfileList =gameJson.getLibfileList();

    libargs<<std::accumulate(libfileList.begin(),libfileList.end(),QString(),
                             [=](QString filenames,QString singleFile){
             return (filenames+=gameProfile.gameDir+"/libraries/"+singleFile+";");
    })
             +gameProfile.gameDir
             +QString("/versions/%1/%1.jar")
             .arg(gameProfile.version);

    return libargs;
}

QStringList game::genGameargs()
{
    return QStringList{gameJson.getMCMainClass()+
                       gameJson.getMCArgs()
                       .replace("${auth_player_name}",gameProfile.username)
                       .replace("${version_name}",gameProfile.version)
                       .replace("${game_directory}",gameProfile.gameDir)
                       .replace("${assets_root}",gameProfile.gameDir+"/assets")
                       .replace("${assets_index_name}",gameJson.getAssetIndex())
                       .replace("${user_type}","Legacy")
                       .replace("${version_type}","Kaminec")};
}


#include <QtNetwork/QNetworkRequest>

QStringList game::checkSession()
{
    return QStringList();
}



int game::extractNatives(QString nativesDir)
{
    auto extractfileList =gameJson.getExtractfileList();

    for(auto& extractfile:extractfileList){

        QString filename = gameProfile.gameDir
                +"/libraries/"
                + extractfile;
        qDebug()<<"filename:"<<filename;
        QFile ef(filename);
        if(!ef.exists()){
            qDebug()<<"Extract file not found.";
            return -1;
        }
        else{
            auto unjar = new QProcess;
            QStringList unzipargs;
            unzipargs<< "x"
                     << filename
                     <<"-o"+nativesDir+"/";
            unjar->start("7za",unzipargs);
        }

    }
    return 0;
}
