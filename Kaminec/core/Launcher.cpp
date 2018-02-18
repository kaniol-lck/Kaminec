#include "Launcher.h"

#include "core/Path.h"
#include "assistance/utility.h"

#include <QDir>
#include <QSettings>
#include <QDebug>

Launcher::Launcher(QObject *parent, Profile profile, LaunchAuth auth) :
	QObject(parent),
	gameParser_(profile, auth),
	gameProcess_(new QProcess(this))
{
	//forward finished infomation
	connect(gameProcess_, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
	//delete natives after playing
	connect(gameProcess_, SIGNAL(finished(int)), this, SLOT(deleteNatives()));
}

void Launcher::start()
{
	auto startcode = gameParser_.getStartcode();

	extractNatives();

	gameProcess_->start(Path::JavaPath(), startcode);
}

void Launcher::extractNatives()
{
	QDir().mkdir(Path::nativesPath());

	auto nativesPaths = gameParser_.getNativesPaths();

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
