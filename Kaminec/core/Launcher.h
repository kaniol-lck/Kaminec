#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QProcess>

#include "core/GameParser.h"

class Launcher : public QObject
{
	Q_OBJECT
public:
	explicit Launcher(QObject *parent);

	void start(const Profile &profile, const LaunchAuth &auth);

	void extractNatives(const QStringList &nativesPaths);

signals:
	void finished(int);
	void exceptionMessage(QString);

public slots:
	void deleteNatives();

private:
	QProcess *gameProcess_;
};

#endif // LAUNCHER_H
