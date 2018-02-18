#include "GameParser.h"

#include "core/Path.h"

GameParser::GameParser(const Profile &profile, const LaunchAuth &auth):
	profile_(profile),
	launchAuth_(auth),
	launchJson_(profile_.lastVersionId_)
{}

QStringList GameParser::getStartcode()
{
	QStringList startcode;
	startcode << getJVMArguments();
	startcode << launchJson_.getMainClass();
	startcode << getGameArguments();

	return startcode;
}

QStringList GameParser::getJVMArguments()
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

QStringList GameParser::getGameArguments()
{
	auto gameArguments = launchJson_.getGameArguments();

	QMap<QString, QString> replace_list = {
		{"${auth_player_name}", QSettings().value("playerName").toString()},
		{"${version_name}", profile_.lastVersionId_},
		{"${game_directory}", profile_.gameDir_},
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

QString GameParser::getClassPaths()
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

QStringList GameParser::getNativesPaths()
{
	QStringList nativesPaths = launchJson_.getNativesPaths();

	for(QString& nativesName : nativesPaths){
		nativesName.prepend(Path::libsPath() + "/");
	}

	return nativesPaths;
}
