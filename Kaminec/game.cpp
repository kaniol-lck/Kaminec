#include "game.h"

#include <QTime>
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
    QTime t;
    auto startcode = this->genStartcode();
    auto time =t.elapsed();

    qDebug()<<"java="<<gameProfile.javaDir<<endl
           <<"args="<<startcode
          <<"Time elapsed:"<<time<<"ms.";

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

    gameProcess.start(
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
    QString nativesPath=gameProfile.gameDir+"/natives";//待改
    this->extractNatives(nativesPath);

    return QStringList
    {
        "-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump",
        "-XX:+UseG1GC",
        "-XX:-UseAdaptiveSizePolicy",
        "-XX:-OmitStackTraceInFastThrow",
        QString("-Xmn%1m").arg(gameProfile.minMem),
        QString("-Xmx%1m").arg(gameProfile.maxMem),
        QString("-Djava.library.path=%1").arg(nativesPath),
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
    return QStringList(gameJson.getMCMainClass()+
                       gameJson.getMCArgs()
                       .replace("${auth_player_name}",gameProfile.username)
                       .replace("${version_name}",gameProfile.version)
                       .replace("${game_directory}",gameProfile.gameDir)
                       .replace("${assets_root}",QString("%1/assets").arg(gameProfile.gameDir))
                       .replace("${assets_index_name}",gameJson.getAssetIndex())
                       .replace("${auth_uuid}","bf500b0b7dcc94d0f803cc980f2b4d3f")
                       .replace("${auth_access_token}","bf500b0b7dcc94d0f803cc980f2b4d3f")
                       .replace("${user_type}","Legacy")
                       .replace("${version_type}","Kaminec").split(" ")<<
                       QString("--height")<<QString::number(gameProfile.height)<<
                       QString("--width")<<QString::number(gameProfile.width));
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
            QStringList unzipargs;
            unzipargs<< "x"
                     << filename
                     <<"-o"+nativesDir+"/";
            QProcess::startDetached("7za",unzipargs);
        }

    }
    return 0;
}
