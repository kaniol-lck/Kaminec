#include "GameParser.h"

#include "assistance/Path.h"

GameParser::GameParser(const Profile &profile, const LaunchAuth &auth):
	profile_(profile),
	launchAuth_(auth),
	launchJson_(profile_.lastVersionId_)
{}

LaunchPack GameParser::getLaunchPack()
{
	if(launchAuth_.getAuthMode()==Mode::Online &&
	   !launchAuth_.validate())
		throw std::runtime_error("Invalid account.");
	return LaunchPack(launchAuth_.getAuthMode(),
					  classPaths(),
					  JVMConfigure(),
					  mainClass(),
					  gameArguments(),
					  versionChain(),
					  nativesFiles());
}

QStringList GameParser::JVMConfigure()
{
	auto range = custom_.getMemoryAllocateRange();

	QStringList JVMArgs{
		"-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump",
		"-XX:+UseG1GC",
		"-XX:-UseAdaptiveSizePolicy",
		"-XX:-OmitStackTraceInFastThrow",
		QString("-Djava.library.path=%1").arg(Path::nativesPath()),
		"-Dfml.ignoreInvalidMinecraftCertificates=true",
		QString("-Xmn%1m").arg(range.first),
		QString("-Xmx%1m").arg(range.second),
		"-Dfml.ignorePatchDiscrepancies=true",
		"-cp"
	};

	return JVMArgs;
}

QStringList GameParser::gameArguments()
{
	auto gameArguments = launchJson_.getGameArguments();

	QMap<QString, QString> replace_list = {
		{"${auth_player_name}", custom_.getPlayerName()},
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

QStringList GameParser::classPaths()
{
	auto libraryPaths = launchJson_.getLibraryPaths();
	auto gameJarPath = launchJson_.getGameJarPath();

	for(auto& libraryPath : libraryPaths)
		libraryPath.prepend(Path::libsPath() + "/");

	gameJarPath.prepend(Path::versionsPath());

	QStringList classPaths;
	classPaths << libraryPaths;
	classPaths << gameJarPath;

	return classPaths;
}

QString GameParser::mainClass()
{
	return launchJson_.getMainClass();
}

QStringList GameParser::versionChain()
{
	return launchJson_.getVersionChain();
}

QStringList GameParser::nativesFiles()
{
	QStringList nativesFiles = launchJson_.getNativesPaths();

	for(QString& nativesName : nativesFiles){
		nativesName.prepend(Path::libsPath() + "/");
	}

	return nativesFiles;
}
