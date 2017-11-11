#include "game.h"
#include "gamemode.h"
#include "profile.h"
#include "downloadmanager.h"
#include "auth.h"

#include <QDir>
#include <QTime>
#include <QUuid>
#include <QDebug>
#include <QSettings>
#include <QStandardPaths>
#include <QProcess>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <algorithm>
#include <QMessageBox>

Game::Game(QObject *parent, Profile gp, Mode gm):
    QObject(parent),
    gameProfile(gp),
	gameMode(gm),
	gameJson(parent,gameProfile.mLastVersionId),
	gameProcess(new QProcess(this)),
	corePath(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).toString())
{}

int Game::start()
{
	if(!QFile(QSettings().value("javaPath").toString()).exists()){
		QMessageBox::warning(0,"Java path error",
							 "javaw.exe does not exist,plaese rechoose!");
		emit finished(0);
		return 0;
	}
///////////////////////////////////////////////////////////////////
    QTime t;
    auto startcode = this->genStartcode();
    auto time =t.elapsed();

	//testTime.txt
	QFile ttf("timeTest.txt");
	ttf.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Append);

	QTextStream out2(&ttf);
	out2<<time<<endl;
/***********************I*am*a*cute*divider*******************************/
	this->extractNatives();
	if(gameMode == Mode::Online){
		auto auth = new Auth(this);
		if(auth->refresh()){
			int index;
			if((index = startcode.indexOf("${auth_uuid}")) != -1)
				startcode.replace(index,auth->getUuid());
			if((index = startcode.indexOf("${auth_access_token}")) != -1)
				startcode.replace(index,auth->getAccessToken());
			if((index = startcode.indexOf("Legacy")) != -1)
				startcode.replace(index,"mojang");
			if(QSettings().value("autoName").toBool()){
				startcode.replace(startcode.indexOf(QSettings().value("playerName").toString()),auth->getPlayerName());
			}
		}else {
			emit finished(0);
			return 0;
		}
	}

	gameProcess->execute(
				QSettings().value("javaPath").toString(),
				startcode);

    connect(gameProcess,SIGNAL(finished(int)),this,SIGNAL(finished(int)));
//	connect(gameProcess,SIGNAL(finished(int)),this,SLOT(deleteNatives()));

	QSettings().setValue("lastUsedVersion", gameProfile.mLastVersionId);
	QSettings().setValue("gameDir", gameProfile.mGameDir);

/***********************I*am*a*cute*divider*******************************/
	QFile logs("logs.txt");
	logs.open(QIODevice::WriteOnly | QIODevice::Text);

	QTextStream out(&logs);
	out<<"java path:"<<QSettings().value("javaPath").toString()<<endl;
	out<<"game arguments:";
	for(auto& i:startcode)out<<i<<" ";
	out<<endl;
	out<<"game directory:"<<gameProfile.mGameDir<<endl;
	out<<"Time used:"<<time<<"ms";

    return 0;
}

QStringList Game::genStartcode()
{
    QStringList startcode;
    startcode<<this->genJVMargs()
             <<this->genLibpath()
			 <<this->genGameArgs()
            ;
    return startcode;
}

QStringList Game::genJVMargs()
{
    return QStringList
    {
        "-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump",
        "-XX:+UseG1GC",
        "-XX:-UseAdaptiveSizePolicy",
        "-XX:-OmitStackTraceInFastThrow",
		QString("-Xmn%1m").arg(QSettings().value("minMem").toString()),
		QString("-Xmx%1m").arg(QSettings().value("maxMem").toString()),
		QString("-Djava.library.path=%1").arg(corePath + "/natives"),
        "-Dfml.ignoreInvalidMinecraftCertificates=true",
		"-Dfml.ignorePatchDiscrepancies=true"
    };
}


QStringList Game::genLibpath()
{
    QStringList libargs;

	QStringList libfileList =gameJson.getLibfileList();

	libargs<<"-cp";

	libargs<<libfileList.join(";");

	return libargs;
}

QStringList Game::genGameArgs()
{
	auto MCArgs = gameJson.getMCArgs();
	qDebug()<<MCArgs;

	int index;

	index = MCArgs.indexOf("${auth_player_name}");
	if(index != -1)
		MCArgs.replace(index,QSettings().value("playerName").toString());
	index = MCArgs.indexOf("${version_name}");
	if(index != -1)
		MCArgs.replace(index,gameProfile.mLastVersionId);
	index = MCArgs.indexOf("${game_directory}");
	if(index != -1)
		MCArgs.replace(index,gameProfile.mGameDir);
	index = MCArgs.indexOf("${assets_root}");
	if(index != -1)
		MCArgs.replace(index,QString("%1/assets").arg(corePath));
	index = MCArgs.indexOf("${assets_index_name}");
	if(index != -1)
		MCArgs.replace(index,gameJson.getAssetIndex());
	index = MCArgs.indexOf("${user_type}");
	if(index != -1)
		MCArgs.replace(index,"Legacy");
	index = MCArgs.indexOf("${version_type}");
	if(index != -1)
		MCArgs.replace(index,"Kaminec Launcher");
	index = MCArgs.indexOf("${user_properties}");
	if(index != -1)
		MCArgs.replace(index,"{}");

	MCArgs<<QString("--height")<<QSettings().value("height").toString()
		  <<QString("--width")<<QSettings().value("width").toString();
    return QStringList(gameJson.getMCMainClass()+MCArgs);
}


int Game::extractNatives()
{
	QString nativesDir = corePath + "/natives";
	QDir().mkpath(nativesDir);
    auto extractfileList =gameJson.getExtractfileList();

    for(auto& extractfile:extractfileList){

		QString filename = corePath
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
					 <<"-o"+nativesDir+"/"
					<<"-aos";
			QProcess::startDetached("7za",unzipargs);
        }

    }
	return 0;
}

bool Game::deleteDirectory(const QString &path)
{
	if (path.isEmpty())
		return false;

	QDir dir(path);
	if(!dir.exists())
		return true;

	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
	QFileInfoList fileList = dir.entryInfoList();
	foreach (QFileInfo fi, fileList)
	{
		if (fi.isFile())
			fi.dir().remove(fi.fileName());
		else
			deleteDirectory(fi.absoluteFilePath());
	}
	return dir.rmpath(dir.absolutePath());
}

void Game::deleteNatives()
{
	QString nativesDir = corePath + "/natives";
	qDebug()<<deleteDirectory(nativesDir);
}
