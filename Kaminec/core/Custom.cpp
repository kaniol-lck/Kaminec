#include "Custom.h"

#include <QCoreApplication>
#include <QStandardPaths>

void Custom::setSelectedProfileName(const QString &selectedProfileName)
{
	settings_.setValue("selectedProfileName", selectedProfileName);
}

QString Custom::getSelectedProfileName() const
{
	return settings_.value("selectedProfileName").toString();
}

void Custom::setLogged(bool flag)
{
	settings_.setValue("logged", flag);
}

bool Custom::getLogged() const
{
	return settings_.value("logged", false).toBool();
}

void Custom::setEmail(const QString &email)
{
	settings_.setValue("email", email);
}

QString Custom::getEmail() const
{
	return settings_.value("email").toString();
}

void Custom::setOnlineMode(bool flag)
{
	settings_.setValue("onlineMode", flag);
}

bool Custom::getOnlineMode() const
{
	return settings_.value("onlineMode").toBool();
}

void Custom::setPlayerName(const QString &playerName)
{
	settings_.setValue("playerName", playerName);
}

QString Custom::getPlayerName() const
{
	return settings_.value("playerName", "Steve").toString();
}

void Custom::setAutoOfficialName(bool flag)
{
	settings_.setValue("autoOfficialName", flag);
}

bool Custom::getAutoOfficialName() const
{
	return settings_.value("autoOfficialName", false).toBool();
}

void Custom::setOfficialName(const QString &officialName)
{
	settings_.setValue("officialName", officialName);
}

QString Custom::getOfficialName() const
{
	return settings_.value("officialName").toString();
}

void Custom::setUuid(const QString &uuid)
{
	settings_.setValue("uuid", uuid);
}

QString Custom::getUuid() const
{
	return settings_.value("uuid").toString();
}

void Custom::setAccessToken(const QString &accessToken)
{
	settings_.setValue("accessToken", accessToken);
}

QString Custom::getAccessToken() const
{
	return settings_.value("accessToken").toString();
}

void Custom::setClientToken(const QString &clientToken)
{
	settings_.value("clientToken", clientToken);
}

QString Custom::getClientToken() const
{
	return settings_.value("clientToken").toString();
}

void Custom::setCoreGameFileDirectory(const QString &coreDirectory)
{
	settings_.setValue("path/corePath", coreDirectory);
}

QString Custom::getCoreGameFileDirectory() const
{
	return settings_.value("path/corePath", QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/.minecraft").toString();
}

void Custom::setDefaultGameDirectory(const QString &gameDirectory)
{
	settings_.setValue("path/gamePath", gameDirectory);
}

QString Custom::getDefaultGameDirectory() const
{
	return settings_.value("path/gamePath", getCoreGameFileDirectory()).toString();
}

void Custom::setJavaDirectory(const QString &JavaDirectory)
{
	settings_.setValue("JavaPath", JavaDirectory);
}

QString Custom::getJavaDirectory() const
{
	return settings_.value("JavaPath").toString();
}

void Custom::setGameVersionsDirectory(const QString &gameVersionsDirectory)
{
	settings_.setValue("path/versionsPath", gameVersionsDirectory);
}

QString Custom::getGameVersionsDirectory() const
{
	return settings_.value("path/versionsPath", "<core>/versions").toString();
}

void Custom::setGameLibrariesDirectory(const QString &gameLibrariesDirectory)
{
	settings_.setValue("path/libsPath", gameLibrariesDirectory);
}

QString Custom::getGameLibrariesDirectory() const
{
	return settings_.value("path/libsPath", "<core>/libraries").toString();
}

void Custom::setAssetsDirectory(const QString &assetsDirectory)
{
	settings_.setValue("path/assetsPath", assetsDirectory);
}

QString Custom::getAssetsDirectory() const
{
	return settings_.value("path/assetsPath", "<core>/assets").toString();
}

void Custom::setAssetsIndexesDirectory(const QString &assetsIndexesDirectory)
{
	settings_.setValue("path/indexesPath", assetsIndexesDirectory);
}

QString Custom::getAssetsIndexes() const
{
	return settings_.value("path/indexesPath", "<assets>/indexes").toString();
}

void Custom::setAssetsObjectsDirectory(const QString &assetsObjectsDirectory)
{
	settings_.setValue("path/objectsPath", assetsObjectsDirectory);
}

QString Custom::getAssetsObjectsDirectory() const
{
	return settings_.value("path/objectsPath", "<assets>/objects").toString();
}

void Custom::setGameNativesDirectory(const QString &gameNativesDirectory)
{
	settings_.setValue("path/nativesPath", gameNativesDirectory);
}

QString Custom::getGameNativesDirectory() const
{
	return settings_.value("path/nativesPath", "<launcher>/natives").toString();
}

void Custom::setUnusedModsDirectory(const QString &unusedModsDirectory)
{
	settings_.setValue("unusedModsDirectory", unusedModsDirectory);
}

QString Custom::getUnusedModsDirectory() const
{
	return settings_.value("unusedModsDirectory", "<game>/unused_mods").toString();
}

void Custom::setSavesBackupDirectory(const QString &savesBackupDirectory)
{
	settings_.setValue("savesBackupDirectory", savesBackupDirectory);
}

QString Custom::getSavesBackupDirectory() const
{
	return settings_.value("savesBackupDirectory", "<game>/savesBackup").toString();
}

void Custom::setMemoryAllocateRange(int minimum, int maximum)
{
	settings_.setValue("minMem", minimum);
	settings_.setValue("maxMem", maximum);
}

void Custom::setMemoryAllocateRange(QPair<int, int> range)
{
	setMemoryAllocateRange(range.first, range.second);
}

QPair<int, int> Custom::getMemoryAllocateRange() const
{
	return qMakePair(settings_.value("minMem", 128).toInt(),
					 settings_.value("maxmem", 1024).toInt());
}

void Custom::setJVMArgumentsPolicy(Custom::JVMArgumentsPolicy policy)
{
	settings_.setValue("JVMArgumentsPolicy", static_cast<int>(policy));
}

Custom::JVMArgumentsPolicy Custom::getJVMArgumentsPolicy()
{
	return static_cast<JVMArgumentsPolicy>(settings_.value("JVMArgumentsPolicy", 0).toInt());
}

void Custom::setCustomJVMArguments(QStringList arguments)
{
	settings_.setValue("customJVMArguments", arguments.join("\\n"));
}


QStringList Custom::getCustomJVMArguments() const
{
	return settings_.value("customJVMArguments").toString().split("\\n");
}

void Custom::setExtraJVMArguments(QStringList arguments)
{
	settings_.setValue("extraJVMArguments", arguments.join("\\n"));
}

QStringList Custom::getExtraJVMArguments() const
{
	return settings_.value("extraJVMArguments").toString().split("\\n");
}

void Custom::setGameWindowFullScreen(bool flag)
{
	settings_.setValue("gameWindowFullScreen", flag);
}

bool Custom::getGameWindowFullScreen() const
{
	return settings_.value("gameWindowFullScreen", false).toBool();
}

void Custom::setCustomGameWindowSize(bool flag)
{
	settings_.setValue("customGameWindowSize", flag);
}

bool Custom::getCustomGameWindowSize() const
{
	return settings_.value("customGameWindowSize", false).toBool();
}

void Custom::setGameWindowSize(int width, int height)
{
	settings_.setValue("GameWindowWidth", width);
	settings_.setValue("GameWindowHeight", height);
}

void Custom::setGameWindowSize(QPair<int, int> size)
{
	setGameWindowSize(size.first, size.second);
}

QPair<int, int> Custom::getGameWindowSize() const
{
	return qMakePair(settings_.value("GameWindowWidth", 854).toInt(),
					 settings_.value("GameWindowHeight", 480).toInt());
}

void Custom::setServerSocket(const QString &socket)
{
	settings_.setValue("serverSocket", socket);
}

QString Custom::setServerSocket() const
{
	return settings_.value("serverSocket").toString();
}

void Custom::setServerMode(bool serverMode)
{
	settings_.setValue("serverMode", serverMode);
}

bool Custom::getServerMode() const
{
	return settings_.value("serverMode", false).toBool();
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

bool Custom::checkFeature(QString featureName)
{
	return settings_.value(featureName, false).toBool();
}
