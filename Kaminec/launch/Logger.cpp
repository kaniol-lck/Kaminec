#include "Logger.h"

#include <QDir>
#include <QTime>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "assistance/Path.h"
#include "exception/Exceptions.hpp"
#include "assistance/utility.h"
#include "assistance/Custom.h"

Logger::Logger(QObject *parent) :
	QObject(parent)
{
	QDir dir(Path::loggerPath());
	if(!dir.exists())
		dir.mkpath(dir.path());
}

void Logger::startLog()
{
	logFile_.setFileName(QString("%1/%2.log")
						 .arg(Path::loggerPath(),
							  QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs).replace(":", "")));
}

void Logger::startGenStartcode()
{
	genStartCodeTime_.start();
}

void Logger::finishGenStartcode()
{
	if(!logFile_.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		throw FileOpenException(logFile_.fileName());
	qDebug()<<logFile_.fileName();
	QTextStream out(&logFile_);
	out << "generate startcode time:" << formatTime(genStartCodeTime_.elapsed()) << endl;
	logFile_.close();
}

void Logger::startGame()
{
	gameTime_.start();
}

void Logger::finishGame()
{
	if(!logFile_.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		throw FileOpenException(logFile_.fileName());
	QTextStream out(&logFile_);
	out << "game time:" << formatTime(gameTime_.elapsed()) << endl;
	logFile_.close();
}

void Logger::logLaunchPack(const LaunchPack &launchPack)
{
	if(!logFile_.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		throw FileOpenException(logFile_.fileName());
	QTextStream out(&logFile_);
	//time
	out << "version chain:" << endl;
	out << versionChain2String(launchPack.versionChain()) << endl << endl;
	out << "java paths:" << endl;
	out << Custom().getJavaDirectory() << endl << endl;
	out << "class paths:" << endl;
	out << launchPack.classPaths().join("\n") << endl << endl;
	out << "game main class:" << endl;
	out << launchPack.mainClass() << endl << endl;
	out << "game arguments:" << endl;
	out << launchPack.gameArguments().toString() << endl << endl;
	out << "JVM arguments:" << endl;
	out << launchPack.JVMConfigure().toString() << endl << endl;
	out << "extract files:" << endl;
	out << launchPack.nativesFiles().join("\n") << endl << endl;
	logFile_.close();
}

QString Logger::versionChain2String(QList<GameVersion> versionChain)
{
	QStringList gameVersionNameList;
	for(auto gameVersion : versionChain)
		gameVersionNameList << gameVersion.versionName();
	return gameVersionNameList.join(" -> ");
}
