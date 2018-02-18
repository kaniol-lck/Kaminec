#include "Launcher.h"

#include "core/Path.h"
#include "core/Arguments.h"
#include "assistance/utility.h"

#include <QDir>
#include <QSettings>
#include <QDebug>

Launcher::Launcher(QObject *parent, Profile profile, LaunchAuth auth) :
	QObject(parent),
	gameProfile_(profile),
	launchAuth_(auth),
	launchJson_(gameProfile_.lastVersionId_),
	gameProcess_(new QProcess(this))
{

}

void Launcher::start()
{
	auto startcode = getStartcode();

	extractNatives();

	gameProcess_->start(Path::JavaPath(),
						startcode);

	//these setting is foolish, migrate it later
	QSettings().setValue("lastUsedVersion", gameProfile_.lastVersionId_);
	QSettings().setValue("gameDir", gameProfile_.gameDir_);
	QSettings().setValue("isOnline", launchAuth_.getAuthMode() == Mode::Online);

	//forward finished infomation
	connect(gameProcess_, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
	//delete natives after playing
	connect(gameProcess_, SIGNAL(finished(int)), this, SLOT(deleteNatives()));

}

QStringList Launcher::getStartcode()
{
	QStringList startcode;
	startcode << getJVMArguments();
	startcode << launchJson_.getMainClass();
	startcode << getGameArguments();

	return startcode;
}

QStringList Launcher::getJVMArguments()
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

QStringList Launcher::getGameArguments()
{
	auto gameArguments = launchJson_.getGameArguments();

	QMap<QString, QString> replace_list = {
		{"${auth_player_name}", QSettings().value("playerName").toString()},
		{"${version_name}", gameProfile_.lastVersionId_},
		{"${game_directory}", gameProfile_.gameDir_},
		{"${assets_root}", Path::assetsPath()},
		{"${auth_uuid}", launchAuth_.getAuthUuid()},
		{"${auth_access_token}", launchAuth_.getAuthAccessToken()},
		{"${user_type}", launchAuth_.getUserType()},
		{"${assets_index_name}", launchJson_.getAssetsIndexId()},
		{"${version_type}", "Kaminec Launcher"},
		{"${user_properties}", "{}"},
	};

	for(auto it = replace_list.begin(); it != replace_list.end(); it++){
		gameArguments.replace(it.key(), it.value());
	}

	return gameArguments.toStringList();
}

QString Launcher::getClassPaths()
{
	auto libraryPaths = launchJson_.getLibraryPaths();
	auto gameJarPath = launchJson_.getGameJarPath();

	for(auto& libraryPath : libraryPaths)
		libraryPath.prepend(Path::libsPath() + "/");

	gameJarPath.prepend(Path::versionsPath());

	QStringList classPaths;
	classPaths << libraryPaths;
	classPaths << gameJarPath;

	return classPaths.join(";");
}

void Launcher::extractNatives()
{
	QDir().mkdir(Path::nativesPath());

	auto extractList = launchJson_.getExtractPaths();

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

void Launcher::deleteNatives()
{
	deleteDirectory(Path::nativesPath());
}
