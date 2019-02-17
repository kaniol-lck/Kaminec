#ifndef LOGGER_H
#define LOGGER_H

#include "messenger/LaunchPack.h"

#include <QObject>
#include <QFile>
#include <QTime>
#include <memory>

class Logger : public QObject
{
	Q_OBJECT
public:
	explicit Logger(QObject *parent);

	void startLog();

	void startGenStartcode();
	void finishGenStartcode();

	void startGame();
	void finishGame();

	void logLaunchPack(const LaunchPack &launchPack);

	static QString versionChain2String(QList<GameVersion> versionChain);
	
signals:

private:
	QFile logFile_;

	QTime genStartCodeTime_;
	QTime gameTime_;

public slots:
};

#endif // LOGGER_H
