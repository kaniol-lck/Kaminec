#include "game.h"
#include "core/Path.h"
#include "core/gamemode.h"
#include "core/json/JsonKit.h"
#include "core/json/JsonManager.h"
#include "messager/profile.h"
#include "assistance/logger.h"

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
#include <QCoreApplication>

Game::Game(QObject *parent, Profile profile, LaunchAuth *auth):
    QObject(parent),
	gameProfile(profile),
	gameAuth(auth),
	gameJson(parent,gameProfile.mLastVersionId),
	gameProcess(new QProcess(this)),
	corePath(Path::corePath()),
	gameLogger(new Logger(this, corePath + "/launcher_log/log.txt"))
{
	connect(gameProcess, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
	connect(gameProcess, SIGNAL(finished(int)), this, SLOT(deleteNatives()));
}

int Game::start()
{
	if(!QFile(QSettings().value("javaPath").toString()).exists()){
		QMessageBox::warning(0,"Java path error",
							 "javaw.exe does not exist,plaese rechoose!");
		emit finished(0);
		return 0;
	}
///////////////////////////////////////////////////////////////////
	gameLogger->startGenStartcode();
    auto startcode = this->genStartcode();

	gameLogger->fisishGenStartcode();

	gameLogger->setVersionChain(gameJson.getVersionChain());

	/*start codes below*/
	this->extractNatives();
	gameProcess->start(
				QSettings().value("javaPath").toString(),
				startcode);

	QSettings().setValue("lastUsedVersion", gameProfile.mLastVersionId);
	QSettings().setValue("gameDir", gameProfile.mGameDir);
	QSettings().setValue("isOnline", gameAuth->getAuthMode() == Mode::Online);

	gameLogger->writeToFile();
    return 0;
}

QStringList Game::genStartcode()
{
    QStringList startcode;
	startcode<<this->genJVMArgs()
			 <<this->genGameArgs()
            ;
    return startcode;
}

QStringList Game::genJVMArgs()
{
	auto JVMArgs = QStringList{
			  "-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump",
			  "-XX:+UseG1GC",
			  "-XX:-UseAdaptiveSizePolicy",
			  "-XX:-OmitStackTraceInFastThrow",
			  QString("-Djava.library.path=%1").arg(Path::nativesPath()),
			  "-Dfml.ignoreInvalidMinecraftCertificates=true",
			  "-Dfml.ignorePatchDiscrepancies=true",
			  "-cp"
		};

	JVMArgs.append(this->genLibpath());

	JVMArgs<<QString("-Xmn%1m").arg(QSettings().value("minMem").toString());
	JVMArgs<<QString("-Xmx%1m").arg(QSettings().value("maxMem").toString());

	gameLogger->setJVMArgs(JVMArgs);

	return JVMArgs;
}


QString Game::genLibpath()
{
	auto libfileList =gameJson.getLibfileList();

	gameLogger->setClassPaths(libfileList);

	auto libArgs = libfileList.join(";");

	return libArgs;
}

QStringList Game::genGameArgs()
{
	auto gameArgs = gameJson.getGameArgs();

	QMap<QString, QString> replace_list = {
		{"${auth_player_name}", QSettings().value("playerName").toString()},
		{"${version_name}", gameProfile.mLastVersionId},
		{"${game_directory}", gameProfile.mGameDir},
		{"${assets_root}", Path::assetsPath()},
		{"${auth_uuid}", gameAuth->getAuthUuid()},
		{"${auth_access_token}", gameAuth->getAuthAccessToken()},
		{"${user_type}", gameAuth->getUserType()},
		{"${assets_index_name}", gameJson.getAssetsIndex()},
		{"${version_type}", "Kaminec Launcher"},
		{"${user_properties}", "{}"},
	};

	for(auto& str : gameArgs){
		if(replace_list.contains(str))
			str = replace_list.value(str);
	}

	if(QSettings().value("fullScreen", false).toBool()){
		gameArgs<<QString("--fullscreen");
	} else{
		gameArgs<<QString("--height")<<QSettings().value("height").toString()
			   <<QString("--width")<<QSettings().value("width").toString();
	}

	auto gameMainClass = gameJson.getGameMainClass();

	gameLogger->setGameMainClass(gameMainClass.join(""));
	gameLogger->setGameArgs(gameArgs);

	return QStringList(gameMainClass + gameArgs);
}


int Game::extractNatives()
{
	QString nativesDir = Path::nativesPath();
	QDir().mkpath(nativesDir);
	gameLogger->setNativesPath(nativesDir);

	auto extractfileList = gameJson.getExtractfileList();

	for(auto& extractfile : extractfileList)
		extractfile.prepend(Path::libsPath() + "/");

	gameLogger->setExtractFiles(extractfileList);

	for(auto& extractfile : extractfileList)
	{
		QFile ef(extractfile);
		qDebug() << extractfile;
		if(!ef.exists()){
			qDebug() << "Extract file not found.";
			return -1;
		} else{
			QStringList unzipargs;
			unzipargs << "x"
					  << extractfile
					  << "-o" + nativesDir + "/"
					  << "-aos";
			QProcess::startDetached("7za", unzipargs);
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
	this->deleteDirectory(Path::nativesPath());
}
