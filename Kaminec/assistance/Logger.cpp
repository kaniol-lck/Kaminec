#include "logger.h"

#include <QTime>
#include <QFile>
#include <QTextStream>

Logger::Logger(QObject *parent, QString logPath) :
	QObject(parent),
	logFile(logPath)
{

}

void Logger::setVersionChain(const QStringList &versionChain)
{
	m_versionChain = versionChain;
}

void Logger::setNativesPath(const QString &nativePath)
{
	m_nativePath = nativePath;
}

void Logger::setClassPaths(const QStringList &classPaths)
{
	m_classPaths = classPaths;
}

void Logger::setGameMainClass(const QString &GameMainClass)
{
	m_gameMainClass = GameMainClass;
}

void Logger::setGameArgs(const QStringList &GameArgs)
{
	m_gameArgs = GameArgs;
}

void Logger::setJVMArgs(const QStringList &JVMArgs)
{
	m_JVMArgs = JVMArgs;
}

void Logger::setExtractFiles(const QStringList &extractFiles)
{
	m_extractFiles = extractFiles;
}

void Logger::startGenStartcode()
{
	genStartCodeTime.start();
}

void Logger::fisishGenStartcode()
{
	startCode_use = genStartCodeTime.elapsed();
}

void Logger::startGame()
{
	gameTime.start();
}

void Logger::finishGame()
{
	game_use = gameTime.elapsed();
}

void Logger::writeToFile()
{
	logFile.open(QIODevice::WriteOnly | QIODevice::Text);

	QTextStream out(&logFile);
	//time
	out << "version chain:" << m_versionChain.join(" -> ") << endl;
	out << "natives path:" << m_nativePath << endl;
	out << "class paths:" << m_classPaths.join("\n") << endl;
	out << "game main class:" << m_gameMainClass << endl;
	out << "game arguements:" << m_gameArgs.join("\n") << endl;
	out << "JVM arguements:" << m_JVMArgs.join("\n") << endl;
	out << "extract files:" << m_extractFiles.join("\n") << endl;
	out << "generate startcode time:" << QString::number(startCode_use) << "ms" << endl;
	out << "play game time:" << QString::number(game_use) << "ms" << endl;
}
