#include "Launcher.h"

#include "assistance/Path.h"
#include "assistance/utility.h"

#include <QDir>
#include <QDebug>

Launcher::Launcher(QObject *parent) :
	QObject(parent),
	gameProcess_(new QProcess(this)),
	logger_(new Logger(this))
{
	//forward finished infomation
	connect(gameProcess_, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
	//delete natives after playing
	connect(gameProcess_, SIGNAL(finished(int)), this, SLOT(deleteNatives()));
}

void Launcher::start(const Profile &profile, const LaunchAuth &auth)
{
	try{
		logger_.startGenStartcode();
		GameParser gameParser(profile, auth);

		auto launchPack = gameParser.getLaunchPack();

		auto startcode = launchPack.startCode();

		logger_.finishGenStartcode();

		extractNatives(launchPack.nativesFiles());
		gameProcess_->start(Path::JavaPath(), startcode);

		logger_.setVersionChain(launchPack.versionChain());
		logger_.setClassPaths(launchPack.classPaths());
		logger_.setGameMainClass(launchPack.mainClass());
		logger_.setGameArgs(launchPack.gameArguments());
		logger_.setJVMArgs(launchPack.JVMConfigure());
		logger_.setNativesFiles(launchPack.nativesFiles());
		logger_.writeToFile();

	}catch(std::exception& e){
		emit exceptionMessage(QString(e.what()));
	}
}

void Launcher::extractNatives(const QStringList &nativesPaths)
{
	QDir().mkdir(Path::nativesPath());


	for(auto extractPath : nativesPaths){
		QFile extractFile(extractPath);
		if(!extractFile.exists()) continue;
		QStringList unzipargs;
		unzipargs << "x"
				  << extractPath
				  << "-o" + Path::nativesPath() + "/"
				  << "-aos";
		QProcess::startDetached("7za", unzipargs);
	}
}

void Launcher::deleteNatives()
{
	deleteDirectory(Path::nativesPath());
}