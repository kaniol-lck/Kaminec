#ifndef CUSTOM_H
#define CUSTOM_H

#include <QSettings>

class Custom
{
public:
	Custom() = default;

	//launcher settings

	void setSelectedProfileName(const QString &selectedProfileName);
	QString getSelectedProfileName() const;

	//account settings

	void setLogged(bool flag = true);
	bool getLogged() const;

	void setEmail(const QString &email);
	QString getEmail() const;

	void setOnlineMode(bool flag = true);
	bool getOnlineMode() const;

	void setPlayerName(const QString &playerName);
	QString getPlayerName() const;

	void setAutoOfficialName(bool flag = true);
	bool getAutoOfficialName() const;

	void setOfficialName(const QString &officialName);
	QString getOfficialName() const;

	void setUuid(const QString &uuid);
	QString getUuid() const;

	void setAccessToken(const QString &accessToken);
	QString getAccessToken() const;

	void setClientToken(const QString &clientToken);
	QString getClientToken() const;

	//directory settings

	void setCoreGameFileDirectory(const QString &coreDirectory);
	QString getCoreGameFileDirectory() const;

	void setDefaultGameDirectory(const QString &gameDirectory);
	QString getDefaultGameDirectory() const;

	void setJavaDirectory(const QString &JavaDirectory);
	QString getJavaDirectory() const;

	void setGameVersionsDirectory(const QString &gameVersionDirectory);
	QString getGameVersionsDirectory() const;

	void setGameLibrariesDirectory(const QString &gameLibrariesDirectory);
	QString getGameLibrariesDirectory() const;

	void setAssetsDirectory(const QString &assetsDirectory);
	QString getAssetsDirectory() const;

	void setAssetsIndexesDirectory(const QString &assetsIndexesDirectory);
	QString getAssetsIndexes() const;

	void setAssetsObjectsDirectory(const QString &assetsObjectsDirectory);
	QString getAssetsObjectsDirectory() const;

	void setGameNativesDirectory(const QString &gameNativesDirectory);
	QString getGameNativesDirectory() const;

	void setUnusedModsDirectory(const QString &unusedModsDirectory);
	QString getUnusedModsDirectory() const;

	void setSavesBackupDirectory(const QString &savesBackupDirectory);
	QString getSavesBackupDirectory() const;

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

	void setExtraJVMArguments(QStringList arguments);
	QStringList getExtraJVMArguments() const;

	//game settings

	void setGameWindowFullScreen(bool flag = true);
	bool getGameWindowFullScreen() const;

	void setCustomGameWindowSize(bool flag = true);
	bool getCustomGameWindowSize() const;

	void setGameWindowSize(int width, int height);
	void setGameWindowSize(QPair<int, int> size);
	QPair<int, int> getGameWindowSize() const;

	void setServerSocket(const QString &socket);
	QString setServerSocket() const;

	void setServerMode(bool serverMode = true);
	bool getServerMode() const;

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

	bool checkFeature(QString featureName);

private:
	QSettings settings_;
};

#endif // CUSTOM_H
