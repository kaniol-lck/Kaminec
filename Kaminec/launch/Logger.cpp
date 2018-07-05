#include "logger.h"

#include <QDir>
#include <QTime>
#include <QDateTime>
#include <QTimeZone>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "assistance/Path.h"
#include "exception/Exceptions.hpp"

Logger::Logger(QObject *parent = 0) :
	QObject(parent)
{}

void Logger::setVersionChain(const QStringList &versionChain)
{
	versionChain_ = versionChain;
}

void Logger::setClassPaths(const QStringList &classPaths)
{
	classPaths_ = classPaths;
}

void Logger::setGameMainClass(const QString &GameMainClass)
{
	gameMainClass_ = GameMainClass;
}

void Logger::setGameArgs(const QStringList &GameArgs)
{
	gameArgs_ = GameArgs;
}

void Logger::setJVMArgs(const QStringList &JVMArgs)
{
	JVMArgs_ = JVMArgs;
}

void Logger::setNativesFiles(const QStringList &extractFiles)
{
	extractFiles_ = extractFiles;
}

void Logger::startGenStartcode()
{
	genStartCodeTime_.start();
}

void Logger::finishGenStartcode()
{
	startCode_use_ = genStartCodeTime_.elapsed();
}

void Logger::startGame()
{
	gameTime_.start();
}

void Logger::finishGame()
{
	game_use_ = gameTime_.elapsed();
}

void Logger::writeToFile()
{
	QDir dir(Path::loggerPath());
	if(!dir.exists())
		dir.mkpath(dir.path());

	auto time = QDateTime::currentDateTime();
	auto offset = time.offsetFromUtc();
	auto zone = QString(offset>0?"+":"") + QString::number(offset);

	QFile logFile(QString("%1/%2UTC%3.log").arg(Path::loggerPath(),
											 time.toString("yyyyMMdd-HHmmss"),
											 zone));

	if(!logFile.open(QIODevice::WriteOnly | QIODevice::Text))
		throw FileOpenException(logFile.fileName());

	QTextStream out(&logFile);
	//time
	out << "version chain:" << versionChain_.join(" -> ") << endl;
	out << "class paths:" << classPaths_.join("\n") << endl;
	out << "game main class:" << gameMainClass_ << endl;
	out << "game arguments:" << gameArgs_.join("\n") << endl;
	out << "JVM arguments:" << JVMArgs_.join("\n") << endl;
	out << "extract files:" << extractFiles_.join("\n") << endl;
	out << "generate startcode time:" << QString::number(startCode_use_) << "ms" << endl;
	out << "play game time:" << QString::number(game_use_) << "ms" << endl;
}
