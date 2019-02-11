#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "messenger/profile.h"

#include <QObject>
#include <QFile>
#include <QJsonObject>
#include <QStandardItemModel>

class ProfileManager : public QObject
{
	Q_OBJECT
public:
	explicit ProfileManager(QObject *parent = nullptr);

	QStandardItemModel* getProfilesModel();

	void initProfiles();

	Profile getProfile(const QString &name) const;
	QMap<QString, Profile> getProfiles() const;
	bool containProfile(const QString &name) const;

	bool insertProfile(const Profile &profile);
	bool removeProfile(const QString &name);

	void setSelectedProfileName(const QString &name);
	QString getSelectedProfileName();

	void setProfileSorting(QString profileSorting);
	QString getProfileSorting() const;

	void setProfileAscending(bool profileAscending);
	bool getProfileAscending() const;

	QString nameFromIndex(const QModelIndex &index) const;
	static QList<QStandardItem*> profile2itemList(const Profile &profile);

	void sort(const QString &accountSorting, bool accountAscending);

	void writeToFile();

public slots:
	void sortRecord(int column);

private:
	QFile profilesFile_;
	QJsonObject profilesObject_;
	QMap<QString, Profile> profilesMap_;

	QStandardItemModel model_;
	enum Column{ Name, LastVersionId, GameDir };
};

#endif // PROFILEMANAGER_H
