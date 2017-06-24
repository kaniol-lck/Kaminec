#include "game.h"
#include "profile.h"
#include "downloadmanager.h"

#include <QDir>
#include <QTime>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <algorithm>

game::game(profile gp, mode gm):
    gameProfile(gp),
    gamemode(gm),
    gameJson(gameProfile.gameDir,gameProfile.version)
{}

int game::start()
{


    //auto gameProcess = new QProcess;
    QTime t;
    auto startcode = this->genStartcode();
    auto time =t.elapsed();

    //qDebug()<<"java="<<gameProfile.javaDir<<endl
    //       <<"args="<<startcode
    //      <<"Time elapsed:"<<time<<"ms.";

        QFile logs("logs.txt");
        logs.open(QIODevice::WriteOnly | QIODevice::Text);

        QTextStream out(&logs);
        out<<"java path:"<<gameProfile.javaDir<<endl;
        out<<"game arguments:";
        for(auto& i:startcode)out<<i<<" ";
        out<<endl;
        out<<"game directory:"<<gameProfile.gameDir<<endl;
        out<<"Time used:"<<time<<"ms";

        //textTime.txt
        QFile ttf("timeTest.txt");
        ttf.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Append);

        QTextStream out2(&ttf);
        out2<<time<<endl;

    auto gameProcess = new QProcess;
    this->extractNatives(gameProfile.gameDir+"/natives");
    gameProcess->start(
                gameProfile.javaDir,
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
        QString("-Djava.library.path=%1").arg(gameProfile.gameDir+"/natives"),
        "-Dfml.ignoreInvalidMinecraftCertificates=true",
        "-Dfml.ignorePatchDiscrepancies=true"
    };
}


QStringList game::genLibpath()
{
    QStringList libargs;

    auto libfileList =gameJson.getLibfileList();

    libargs<<"-cp"
           <<std::accumulate(libfileList.begin(),libfileList.end(),QString(""),
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
    auto MCArgs = gameJson.getMCArgs();

    MCArgs.replace(MCArgs.indexOf("${auth_player_name}"),gameProfile.username);
    MCArgs.replace(MCArgs.indexOf("${version_name}"),gameProfile.version);
    MCArgs.replace(MCArgs.indexOf("${game_directory}"),gameProfile.gameDir);
    MCArgs.replace(MCArgs.indexOf("${assets_root}"),QString("%1/assets").arg(gameProfile.gameDir));
    MCArgs.replace(MCArgs.indexOf("${assets_index_name}"),gameJson.getAssetIndex());
    MCArgs.replace(MCArgs.indexOf("${auth_uuid}"),"bf500b0b7dcc94d0f803cc980f2b4d3f");
    MCArgs.replace(MCArgs.indexOf("${auth_access_token}"),"bf500b0b7dcc94d0f803cc980f2b4d3f");
    MCArgs.replace(MCArgs.indexOf("${user_type}"),"Legacy");
    MCArgs.replace(MCArgs.indexOf("${version_type}"),"Kaminec Launcher");
    MCArgs<<QString("--height")<<QString::number(gameProfile.height)
          <<QString("--width")<<QString::number(gameProfile.width);
    return QStringList(gameJson.getMCMainClass()+MCArgs);
}


#include <QtNetwork/QNetworkRequest>

QStringList game::checkSession()
{
    return QStringList();
}



int game::extractNatives(QString nativesDir)
{
    QDir nd(nativesDir);
    if(nd.entryList().size()==12) return 1;//检查是否已存在natives

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
            QStringList unzipargs;
            unzipargs<< "x"
                     << filename
                     <<"-o"+nativesDir+"/";
            QProcess::startDetached("7za",unzipargs);
        }

    }
    return 0;
}
