#include "Launcher.h"

#include "assistance/Path.h"
#include "assistance/utility.h"

#include <QDir>
#include <QDebug>

#include <JlCompress.h>

Launcher::Launcher(QObject *parent) :
	QObject(parent),
	gameProcess_(new QProcess(this)),
	logger_(new Logger(this))
{
	//forward finished infomation
	connect(gameProcess_, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
	//delete natives after playing
	connect(gameProcess_, SIGNAL(finished(int)), this, SLOT(gameFinished()));
}

void Launcher::start(const Profile &profile, const Account &account)
{
	try{
		logger_.startLog();
		logger_.startGenStartcode();
		LaunchParser launchParser(profile, account);

		auto launchPack = launchParser.getLaunchPack();

		auto startcode = launchPack.startCode();

		logger_.finishGenStartcode();

		extractNatives(launchPack.nativesFiles());

		gameProcess_->setProgram(Path::JavaPath());
		gameProcess_->setArguments(startcode);
		gameProcess_->start();
		logger_.startGame();

		logger_.logLaunchPack(launchPack);

	}catch(std::exception& e){
		emit exceptionMessage(QString(e.what()));
	}
}

void Launcher::extractNatives(const QStringList &nativesPaths)
{
	QDir().mkdir(Path::nativesPath());

	for(auto extractPath : nativesPaths){
		if(!QFile(extractPath).exists()) continue;
		JlCompress::extractDir(extractPath, Path::nativesPath());
	}
}

void Launcher::gameFinished()
{
	deleteDirectory(Path::nativesPath());
	logger_.finishGame();
}
