#ifndef GAMEDOWNLOAD_H
#define GAMEDOWNLOAD_H

#include <QObject>
#include <QFile>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

#include "messenger/GameVersion.h"

class GameDownload : public QObject
{
	Q_OBJECT
public:
	explicit GameDownload(QObject *parent = nullptr);

	QAbstractItemModel *getModel();
	void loadVersions();

	GameVersion getGameVersion(const QString &versionName) const;

	enum Column{ Id, Type, Time, ReleaseTime, Url };

public slots:
	void reapplyFilter(bool enableSnapshot, bool enableOldBeta, bool enableOldAlpha);

	void loadManifest();

private:
	QFile manifestFile_;
	QJsonObject manifestObject_;
	QMap<QString, GameVersion> versionsMap_;

	QStandardItemModel model_;
	QSortFilterProxyModel proxyModel_;
};

#endif // GAMEDOWNLOAD_H
