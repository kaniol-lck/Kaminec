#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTime>

class Logger : public QObject
{
	Q_OBJECT
public:
	explicit Logger(QObject *parent, QString logPath);

	void setVersionChain(const QStringList& versionChain);
	void setNativesPath(const QString& nativePath);
	void setClassPaths(const QStringList& classPaths);
	void setGameMainClass(const QString& GameMainClass);
	void setGameArgs(const QStringList& GameArgs);
	void setJVMArgs(const QStringList& JVMArgs);
	void setExtractFiles(const QStringList& extractFiles);

	void startGenStartcode();
	void fisishGenStartcode();

	void startGame();
	void finishGame();

	void writeToFile();
	
signals:

private:
	QFile logFile;
	QStringList m_versionChain;
	QString m_nativePath;
	QStringList m_classPaths;
	QString m_gameMainClass;
	QStringList m_gameArgs;
	QStringList m_JVMArgs;
	QStringList m_extractFiles;

	int startCode_use;
	int game_use;

	QTime genStartCodeTime;
	QTime gameTime;

public slots:
};

#endif // LOGGER_H
