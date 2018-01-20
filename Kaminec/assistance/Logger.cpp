#include "logger.h"

#include <QTime>
#include <QFile>
#include <QTextStream>

Logger::Logger(QObject *parent, QString logPath) :
	QObject(parent),
	logFile_(logPath)
{

}

void Logger::setVersionChain(const QStringList &versionChain)
{
	versionChain_ = versionChain;
}

void Logger::setNativesPath(const QString &nativePath)
{
	nativePath_ = nativePath;
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

void Logger::setExtractFiles(const QStringList &extractFiles)
{
	extractFiles_ = extractFiles;
}

void Logger::startGenStartcode()
{
	genStartCodeTime_.start();
}

void Logger::fisishGenStartcode()
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
	logFile_.open(QIODevice::WriteOnly | QIODevice::Text);

	QTextStream out(&logFile_);
	//time
	out << "version chain:" << versionChain_.join(" -> ") << endl;
	out << "natives path:" << nativePath_ << endl;
	out << "class paths:" << classPaths_.join("\n") << endl;
	out << "game main class:" << gameMainClass_ << endl;
	out << "game arguments:" << gameArgs_.join("\n") << endl;
	out << "JVM arguments:" << JVMArgs_.join("\n") << endl;
	out << "extract files:" << extractFiles_.join("\n") << endl;
	out << "generate startcode time:" << QString::number(startCode_use_) << "ms" << endl;
	out << "play game time:" << QString::number(game_use_) << "ms" << endl;
}
