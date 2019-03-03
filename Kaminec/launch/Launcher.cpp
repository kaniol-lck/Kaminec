#include "Launcher.h"

#include "assistance/Path.h"
#include "assistance/utility.h"

#include <QDir>
#include <QDebug>

#include <JlCompress.h>

Launcher::Launcher(QObject *parent) :
	QObject(parent),
	gameProcess_(new QProcess()),
	logger_(new Logger(this))
{
	connect(gameProcess_, &QProcess::stateChanged, this, &Launcher::stateChanged);
	connect(gameProcess_, &QProcess::readyRead, [&]{model_.appendRow(new QStandardItem(QString(gameProcess_->readAll()).trimmed()));});
	//delete natives after playing
	connect(gameProcess_, static_cast<void(QProcess::*)(int)>(&QProcess::finished), [&](int i){
		logger_.finishGame();
		deleteDirectory(Path::nativesPath());
		emit finished(i);
	});
}

QStandardItemModel *Launcher::getOutputModel()
{
	return &model_;
}

void Launcher::start(const Profile &profile, const Account &account)
{
	model_.clear();
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
