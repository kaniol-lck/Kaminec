#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QObject>
#include <QJsonObject>

class ProfileManager : public QObject
{
	Q_OBJECT
public:
	explicit ProfileManager(QObject *parent = nullptr);

signals:

public slots:

private:
	QJsonObject profilesMgrDoc;
};

#endif // PROFILEMANAGER_H
