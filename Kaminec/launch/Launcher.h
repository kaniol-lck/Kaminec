#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QProcess>

#include "launch/LaunchParser.h"
#include "launch/Logger.h"

class Launcher : public QObject
{
	Q_OBJECT
public:
	explicit Launcher(QObject *parent = nullptr);

	void start(const Profile &profile, const Account &account);

	void extractNatives(const QStringList &nativesPaths);

signals:
	void finished(int);
	void stateChanged(QProcess::ProcessState);
	void exceptionMessage(QString);

private:
	QProcess *gameProcess_;
	Logger logger_;
};

#endif // LAUNCHER_H
