#include "LaunchParser.h"

#include "assistance/Path.h"
#include "assistance/PathReplacer.h"
#include "exception/Exceptions.hpp"

LaunchParser::LaunchParser(const Profile &profile, const LaunchAuth &auth):
	profile_(profile),
	launchAuth_(auth),
	launchJson_(profile_.lastVersionId_)
{}

LaunchPack LaunchParser::getLaunchPack() const
{
	if(launchAuth_.getAuthMode()==Mode::Online &&
	   !launchAuth_.validate())
		throw InvalidAccountException(Custom().getEmail());
	return LaunchPack(launchAuth_.getAuthMode(),
					  classPaths(),
					  JVMConfigure(),
					  mainClass(),
					  gameArguments(),
					  versionChain(),
					  nativesFiles());
}

QStringList LaunchParser::JVMConfigure() const
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

QStringList LaunchParser::gameArguments() const
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

QStringList LaunchParser::classPaths() const
{
	auto libraryPaths = launchJson_.getLibraryPaths();
	auto gameJarPath = launchJson_.getGameJarPath();

	for(auto& libraryPath : libraryPaths)
		PathReplacer::replace(libraryPath);

	PathReplacer::replace(gameJarPath);

	QStringList classPaths;
	classPaths << libraryPaths;
	classPaths << gameJarPath;

	return classPaths;
}

QString LaunchParser::mainClass() const
{
	return launchJson_.getMainClass();
}

QStringList LaunchParser::versionChain() const
{
	return launchJson_.getVersionChain();
}

QStringList LaunchParser::nativesFiles() const
{
	QStringList nativesFiles = launchJson_.getNativesPaths();

	for(QString& nativesName : nativesFiles){
		PathReplacer::replace(nativesName);
	}

	return nativesFiles;
}
