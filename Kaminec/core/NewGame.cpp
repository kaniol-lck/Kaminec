#include "NewGame.h"

#include "core/Path.h"
#include "core/Arguments.h"
#include "assistance/utility.h"

#include <QDir>
#include <QSettings>
#include <QDebug>

NewGame::NewGame(QObject *parent, Profile profile, LaunchAuth *auth) :
	QObject(parent),
	gameProfile(profile),
	launchAuth(auth),
	launchJson(gameProfile.mLastVersionId),
	gameProcess(new QProcess(this))
{

}

void NewGame::start()
{
	auto startcode = getStartcode();

	extractNatives();

	gameProcess->start(Path::JavaPath(),
					   startcode);

	//these setting is foolish, migrate it later
	QSettings().setValue("lastUsedVersion", gameProfile.mLastVersionId);
	QSettings().setValue("gameDir", gameProfile.mGameDir);
	QSettings().setValue("isOnline", launchAuth->getAuthMode() == Mode::Online);

	//forward finished infomation
	connect(gameProcess, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
	//delete natives after playing
	connect(gameProcess, SIGNAL(finished(int)), this, SLOT(deleteNatives()));

}

QStringList NewGame::getStartcode()
{
	QStringList startcode;
	startcode << getJVMArguments();
	startcode << launchJson.getMainClass();
	startcode << getGameArguments();

	return startcode;
}

QStringList NewGame::getJVMArguments()
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

	JVMArgs.append(getClassPaths());

	JVMArgs<<QString("-Xmn%1m").arg(QSettings().value("minMem").toString());
	JVMArgs<<QString("-Xmx%1m").arg(QSettings().value("maxMem").toString());

	return JVMArgs;
}

QStringList NewGame::getGameArguments()
{
	auto gameArguments = launchJson.getGameArguments();

	QMap<QString, QString> replace_list = {
		{"${auth_player_name}", QSettings().value("playerName").toString()},
		{"${version_name}", gameProfile.mLastVersionId},
		{"${game_directory}", gameProfile.mGameDir},
		{"${assets_root}", Path::assetsPath()},
		{"${auth_uuid}", launchAuth->getAuthUuid()},
		{"${auth_access_token}", launchAuth->getAuthAccessToken()},
		{"${user_type}", launchAuth->getUserType()},
		{"${assets_index_name}", launchJson.getAssetsIndexId()},
		{"${version_type}", "Kaminec Launcher"},
		{"${user_properties}", "{}"},
	};

	for(auto it = replace_list.begin(); it != replace_list.end(); it++){
		gameArguments.replace(it.key(), it.value());
	}

	return gameArguments.toStringList();
}

QString NewGame::getClassPaths()
{
	auto libraryPaths = launchJson.getLibraryPaths();
	auto gameJarPath = launchJson.getGameJarPath();

	for(auto& libraryPath : libraryPaths)
		libraryPath.prepend(Path::libsPath() + "/");

	gameJarPath.prepend(Path::versionsPath());

	QStringList classPaths;
	classPaths << libraryPaths;
	classPaths << gameJarPath;

	return classPaths.join(";");
}

void NewGame::extractNatives()
{
	QDir().mkdir(Path::nativesPath());

	auto extractList = launchJson.getExtractPaths();

	for(auto extractName : extractList){
		auto extractPath = Path::libsPath() + "/" + extractName;
		qDebug()<<extractPath;
		QFile extractFile(extractPath);
		if(!extractFile.exists()) continue;
		QStringList unzipargs;
		unzipargs << "x"
				  << extractPath
				  << "-o" + Path::nativesPath() + "/"
				  << "-aos";
		QProcess::startDetached("7za", unzipargs);
	}
}

void NewGame::deleteNatives()
{
	deleteDirectory(Path::nativesPath());
}