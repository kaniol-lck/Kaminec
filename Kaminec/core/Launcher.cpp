#include "Launcher.h"

#include "core/Path.h"
#include "assistance/utility.h"

#include <QDir>
#include <QSettings>

Launcher::Launcher(QObject *parent) :
	QObject(parent),
	gameProcess_(new QProcess(this))
{
	//forward finished infomation
	connect(gameProcess_, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
	//delete natives after playing
	connect(gameProcess_, SIGNAL(finished(int)), this, SLOT(deleteNatives()));
}

void Launcher::start(const Profile &profile, const LaunchAuth &auth)
{
	try{
		GameParser gameParser(profile, auth);

		auto startcode = gameParser.getStartcode();

		extractNatives(gameParser.getNativesPaths());

		gameProcess_->start(Path::JavaPath(), startcode);
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
