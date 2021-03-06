#include "LaunchParser.h"

#include "assistance/Path.h"
#include "assistance/PathReplacer.h"
#include "exception/Exceptions.hpp"

LaunchParser::LaunchParser(const Profile &profile, const Account &account):
	profile_(profile),
	account_(account),
	launchJson_(profile_.lastVersionId().versionName())
{}

LaunchPack LaunchParser::getLaunchPack() const
{
	return LaunchPack(account_.mode(),
					  classPaths(),
					  JVMConfigure(),
					  mainClass(),
					  gameArguments(),
					  versionChain(),
					  nativesFiles());
}

Arguments LaunchParser::JVMConfigure() const
{
	auto range = custom_.getMemoryAllocateRange();

	Arguments JVMArgs;
    JVMArgs.setOption("-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump");
    JVMArgs.setOption(QString("-Djava.library.path=%1").arg(Path::nativesPath()));
    JVMArgs.setOption("-Dfml.ignoreInvalidMinecraftCertificates=true");
    JVMArgs.setOption(QString("-Xmn%1m").arg(range.first));
    JVMArgs.setOption(QString("-Xmx%1m").arg(range.second));
    JVMArgs.setOption("-Dfml.ignorePatchDiscrepancies=true");

    if(custom_.getUseCustomJVMArguments()){
        for(const auto& arg : custom_.getCustomJVMArguments())
            JVMArgs.setOption(arg);
    }

	return JVMArgs;
}

Arguments LaunchParser::gameArguments() const
{
	auto gameArguments = launchJson_.getGameArguments();
	auto size = custom_.getGameWindowSize();
	QMap<QString, QString> replace_list = {
		{"${auth_player_name}", account_.playername()},
		{"${auth_uuid}", account_.uuid()},
		{"${version_name}", profile_.lastVersionId().versionName()},
        {"${game_directory}", profile_.gameDir().isEmpty()?custom_.getDefaultGameDirectory():profile_.gameDir()},
		{"${assets_root}", Path::assetsPath()},
		{"${assets_index_name}", launchJson_.getAssetsIndexId()},
		{"${version_type}", "Kaminec Launcher"},
		{"${user_properties}", "{}"},
		{"${resolution_width}", QString::number(size.first)},
		{"${resolution_height}", QString::number(size.second)},
	};

	if(account_.mode()==GameMode::Certified){
		replace_list.insert("${auth_access_token}", account_.accessToken());
		replace_list.insert("${user_type}", "mojang");
	} else{
		replace_list.insert("${user_type}", "Legacy");
	}

	if(custom_.getFullScreen())
		gameArguments.setOption("--fullscreen");

	if(custom_.getServerMode()){
		gameArguments.setOption("--server", custom_.getServer());
		gameArguments.setOption("--port", custom_.getServerPort());
	}

	for(auto it = replace_list.begin(); it != replace_list.end(); it++){
		gameArguments.replace(it.key(), it.value());
	}

	return gameArguments;
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

QList<GameVersion> LaunchParser::versionChain() const
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
