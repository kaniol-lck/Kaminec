#ifndef CUSTOM_H
#define CUSTOM_H

#include <QSettings>
#include <QCoreApplication>
#include <QFont>
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
        settings_.setValue(QString(prefix) + "/" + #key, key);\
	}\
	\
	decltype(QVariant().to##type()) get##name() const{\
        return settings_.value(QString(prefix) + "/" + #key, defaultValue).to##type();\
	}

class Custom
{
public:
	Custom();

	//launcher settings
	getterAndSetter(LogFileNumber, Int, logFileNumber, 10)
	getterAndSetter(Font, String, font, QFont("微软雅黑", 9))
	getterAndSetter(Background, String, background, ":/main/res/background.png")
    getterAndSetter(UseDefaultPath, Bool, useDefaultPath, true)
	getterAndSetter(UseBMCLAPI, Bool, useBMCLAPI, false)

	//directory settings
    getterAndSetter_prefix(CoreGameFileDirectory, String, coreDirectory, "path", QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/.minecraft")
    getterAndSetter_prefix(DefaultGameDirectory, String, gameDirectory, "path", getCoreGameFileDirectory())
    getterAndSetter_prefix(JavaDirectory, String, JavaDirectory, "path", "javaw")
    getterAndSetter_prefix(GameVersionsDirectory, String, gameVersionDirectory, "path", "<core>/versions")
    getterAndSetter_prefix(GameLibrariesDirectory, String, gameLibrariesDirectory, "path", "<core>/libraries")
    getterAndSetter_prefix(AssetsDirectory, String, assetsDirectory, "path", "<core>/assets")
    getterAndSetter_prefix(AssetsIndexesDirectory, String, assetsIndexesDirectory, "path", "<assets>/indexes")
    getterAndSetter_prefix(AssetsObjectsDirectory, String, assetsObjectsDirectory, "path", "<assets>/objects")
    getterAndSetter_prefix(GameNativesDirectory, String, gameNativesDirectory, "path", "<launcher>/natives")
    getterAndSetter_prefix(UnusedModsDirectory, String, unusedModsDirectory, "path", "<game>/unused_mods")
    getterAndSetter_prefix(SavesBackupDirectory, String, savesBackupDirectory, "path", "<game>/savesBackup")
    getterAndSetter_prefix(LoggerDirectory, String, loggerDirectory, "path", "<launcher>/launcher_logs")

    //download display settings
    getterAndSetter_prefix(HideTime, Bool, hideTime, "downloadDisplay", true)
    getterAndSetter_prefix(HideReleaseTime, Bool, hideReleaseTime, "downloadDisplay", true)
    getterAndSetter_prefix(HideUrl, Bool, hideUrl, "downloadDisplay", true)

    getterAndSetter_prefix(EnableSnapsot, Bool, enableSnapsot ,"downloadDisplay", true)
    getterAndSetter_prefix(EnableOldBeta, Bool, enableOldBeta ,"downloadDisplay", true)
    getterAndSetter_prefix(EnableOldAlpha, Bool, enableOldAlpha ,"downloadDisplay", true)

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

    getterAndSetter(UseCustomJVMArguments, Bool, useCustomJVMArguments, false)
	void setCustomJVMArguments(QStringList arguments);
	QStringList getCustomJVMArguments() const;

	void setLanguage(QString &language);
	QString getLanguage() const;

	//game settings

	getterAndSetter(FullScreen, Bool, fullScreen, false)
	getterAndSetter(CustomizeResolution, Bool, customizeResolution, false)

	void setGameWindowSize(int width, int height);
	void setGameWindowSize(QPair<int, int> size);
	QPair<int, int> getGameWindowSize() const;

	getterAndSetter(Server, String, server, "")
	getterAndSetter(ServerPort, String, port, 25565)
	getterAndSetter(ServerMode, Bool, serverMode, false)

private:
	QSettings settings_;
};

#undef getterAndSetter
#undef getterAndSetter_prefix

#endif // CUSTOM_H
