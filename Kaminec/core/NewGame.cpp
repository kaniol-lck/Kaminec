#include "NewGame.h"

#include "core/Path.h"
#include "core/Arguements.h"

#include <QDir>
#include <QSettings>
#include <QDebug>

NewGame::NewGame(QObject *parent, Profile profile, LaunchAuth *auth) :
	QObject(parent),
	gameProfile(profile),
	launchAuth(auth),
	gameJson(gameProfile.mLastVersionId),
	gameProcess(new QProcess(this))
{

}

void NewGame::start()
{
	auto startcode = getStartcode();

	qDebug()<<startcode;

	this->extractNatives();

	gameProcess->start(Path::JavaPath(),
					   startcode);

	QSettings().setValue("lastUsedVersion", gameProfile.mLastVersionId);
	QSettings().setValue("gameDir", gameProfile.mGameDir);
	QSettings().setValue("isOnline", launchAuth->getAuthMode() == Mode::Online);

}

QStringList NewGame::getStartcode()
{
	QStringList startcode;
	startcode << getJVMArguements();
	startcode << gameJson.getMainClass();
	startcode << getGameArguements();

	return startcode;
}

QStringList NewGame::getJVMArguements()
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

QStringList NewGame::getGameArguements()
{
	auto gameArguements = gameJson.getGameArguements();

	QMap<QString, QString> replace_list = {
		{"${auth_player_name}", QSettings().value("playerName").toString()},
		{"${version_name}", gameProfile.mLastVersionId},
		{"${game_directory}", gameProfile.mGameDir},
		{"${assets_root}", Path::assetsPath()},
		{"${auth_uuid}", launchAuth->getAuthUuid()},
		{"${auth_access_token}", launchAuth->getAuthAccessToken()},
		{"${user_type}", launchAuth->getUserType()},
		{"${assets_index_name}", gameJson.getAssetsIndex()},
		{"${version_type}", "Kaminec Launcher"},
		{"${user_properties}", "{}"},
	};

	for(auto it = replace_list.begin(); it != replace_list.end(); it++){
		gameArguements.replace(it.key(), it.value());
	}

	return gameArguements.toStringList();
}

QString NewGame::getClassPaths()
{
	auto libraryPaths = gameJson.getLibraryPaths();
	auto gameJarPath = gameJson.getGameJarPath();

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

	auto extractList = gameJson.getExtractPaths();

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

}
