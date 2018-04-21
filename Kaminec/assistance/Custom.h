#ifndef CUSTOM_H
#define CUSTOM_H

#include <QSettings>
#include <QCoreApplication>
#include <QStandardPaths>

#define getterAndSetter(name, type, key, defaultValue) \
	void set##name(const decltype(QVariant().to##type()) &key){\
		settings_.setValue(#key, key);\
	}\
	\
	decltype(QVariant().to##type()) get##name() const{\
		return settings_.value(#key, defaultValue).to##type();\
	}

#define getterAndSetter_prefix(name, type, key, prefix, defaultValue) \
	void set##name(const decltype(QVariant().to##type()) &key){\
		settings_.setValue(QString(prefix) + #key, key);\
	}\
	\
	decltype(QVariant().to##type()) get##name() const{\
		return settings_.value(QString(prefix) + #key, defaultValue).to##type();\
	}

class Custom
{
public:
	Custom() = default;

	//launcher settings
	getterAndSetter(SelectedProfileName, String, selectedProfileName, "")

	//account settings
	getterAndSetter(Logged, Bool, logged, false)
	getterAndSetter(Email, String, email, "")
	getterAndSetter(OnlineMode, Bool, onlineMode, false)

	getterAndSetter(PlayerName, String, playerName, "Steve")
	getterAndSetter(AutoOfficialName, Bool, autoOfficialName, false)
	getterAndSetter(OfficialName, String, officialName, "")
	getterAndSetter(Uuid, String, uuid, "")
	getterAndSetter(AccessToken, String, accessToken, "")
	getterAndSetter(ClientToken, String, clientToken, "")

	//directory settings
	getterAndSetter_prefix(CoreGameFileDirectory, String, coreDirectory, "path/", QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/.minecraft")
	getterAndSetter_prefix(DefaultGameDirectory, String, gameDirectory, "path/", getCoreGameFileDirectory())
	getterAndSetter_prefix(JavaDirectory, String, JavaDirectory, "path/", "")
	getterAndSetter_prefix(GameVersionsDirectory, String, gameVersionDirectory, "path/", "<core>/versions")
	getterAndSetter_prefix(GameLibrariesDirectory, String, gameLibrariesDirectory, "path/", "<core>/libraries")
	getterAndSetter_prefix(AssetsDirectory, String, assetsDirectory, "path/", "<core>/assets")
	getterAndSetter_prefix(AssetsIndexesDirectory, String, assetsIndexesDirectory, "path/", "<assets>/indexes")
	getterAndSetter_prefix(AssetsObjectsDirectory, String, assetsObjectsDirectory, "path/", "<assets>/objects")
	getterAndSetter_prefix(GameNativesDirectory, String, gameNativesDirectory, "path/", "<launcher>/natives")
	getterAndSetter_prefix(UnusedModsDirectory, String, unusedModsDirectory, "path/", "<game>/unused_mods")
	getterAndSetter_prefix(SavesBackupDirectory, String , savesBackupDirectory, "path/", "<game>/savesBackup")

	//JVM settings
	void setMemoryAllocateRange(int minimum, int maximum);
	void setMemoryAllocateRange(QPair<int, int> range);
	QPair<int, int> getMemoryAllocateRange() const;

	enum class JVMArgumentsPolicy{
		Kaminec,
		Official,
		Custom
	};

	void setJVMArgumentsPolicy(JVMArgumentsPolicy policy);
	JVMArgumentsPolicy getJVMArgumentsPolicy();

	void setCustomJVMArguments(QStringList arguments);
	QStringList getCustomJVMArguments() const;

	//game settings

	getterAndSetter(GameWindowFullScreen, Bool, gameWindowFullScreen, false)
	getterAndSetter(CustomGameWindowSize, Bool, customGameWindowSize, false)

	void setGameWindowSize(int width, int height);
	void setGameWindowSize(QPair<int, int> size);
	QPair<int, int> getGameWindowSize() const;

	getterAndSetter(ServerSocket, String, serverSocket, "")
	getterAndSetter(ServerMode, Bool, serverMode, false)

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

	bool checkFeature(QString featureName);

private:
	QSettings settings_;
};

#undef getterAndSetter
#undef getterAndSetter_prefix

#endif // CUSTOM_H
