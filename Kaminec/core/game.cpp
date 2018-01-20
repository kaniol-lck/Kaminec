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
	gameProfile_(profile),
	gameAuth_(auth),
	gameJson_(parent,gameProfile_.lastVersionId_),
	gameProcess_(new QProcess(this)),
	corePath_(Path::corePath()),
	gameLogger_(new Logger(this, corePath_ + "/launcher_log/log.txt"))
{
	connect(gameProcess_, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
	connect(gameProcess_, SIGNAL(finished(int)), this, SLOT(deleteNatives()));
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
	gameLogger_->startGenStartcode();
    auto startcode = this->genStartcode();

	gameLogger_->fisishGenStartcode();

	gameLogger_->setVersionChain(gameJson_.getVersionChain());

	/*start codes below*/
	this->extractNatives();
	gameProcess_->start(
				QSettings().value("javaPath").toString(),
				startcode);

	QSettings().setValue("lastUsedVersion", gameProfile_.lastVersionId_);
	QSettings().setValue("gameDir", gameProfile_.gameDir_);
	QSettings().setValue("isOnline", gameAuth_->getAuthMode() == Mode::Online);

	gameLogger_->writeToFile();
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

	gameLogger_->setJVMArgs(JVMArgs);

	return JVMArgs;
}


QString Game::genLibpath()
{
	auto libfileList =gameJson_.getLibfileList();

	gameLogger_->setClassPaths(libfileList);

	auto libArgs = libfileList.join(";");

	return libArgs;
}

QStringList Game::genGameArgs()
{
	auto gameArgs = gameJson_.getGameArgs();

	QMap<QString, QString> replace_list = {
		{"${auth_player_name}", QSettings().value("playerName").toString()},
		{"${version_name}", gameProfile_.lastVersionId_},
		{"${game_directory}", gameProfile_.gameDir_},
		{"${assets_root}", Path::assetsPath()},
		{"${auth_uuid}", gameAuth_->getAuthUuid()},
		{"${auth_access_token}", gameAuth_->getAuthAccessToken()},
		{"${user_type}", gameAuth_->getUserType()},
		{"${assets_index_name}", gameJson_.getAssetsIndex()},
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

	auto gameMainClass = gameJson_.getGameMainClass();

	gameLogger_->setGameMainClass(gameMainClass.join(""));
	gameLogger_->setGameArgs(gameArgs);

	return QStringList(gameMainClass + gameArgs);
}


int Game::extractNatives()
{
	QString nativesDir = Path::nativesPath();
	QDir().mkpath(nativesDir);
	gameLogger_->setNativesPath(nativesDir);

	auto extractfileList = gameJson_.getExtractfileList();

	for(auto& extractfile : extractfileList)
		extractfile.prepend(Path::libsPath() + "/");

	gameLogger_->setExtractFiles(extractfileList);

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
