#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTime>

class Logger : public QObject
{
	Q_OBJECT
public:
	explicit Logger(QObject *parent, const QString &logPath);

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
	QFile logFile_;
	QStringList versionChain_;
	QString nativePath_;
	QStringList classPaths_;
	QString gameMainClass_;
	QStringList gameArgs_;
	QStringList JVMArgs_;
	QStringList extractFiles_;

	int startCode_use_;
	int game_use_ = 0;

	QTime genStartCodeTime_;
	QTime gameTime_;

public slots:
};

#endif // LOGGER_H
