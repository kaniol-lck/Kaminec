#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QObject>
#include <QJsonObject>

class ProfileManager : public QObject
{
	Q_OBJECT
public:
	explicit ProfileManager(QObject *parent = nullptr);

	bool checkVersion(const QString &version);
	void addVersion(const QString &version, const QString &gamePath);

signals:

public slots:

private:
	QJsonObject profilesMgrObj_;
};

#endif // PROFILEMANAGER_H
