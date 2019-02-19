#include "UI/kamineclauncher.h"

#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include "assistance/Custom.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Kaniol");
	QCoreApplication::setApplicationName("KaminecLauncher");
	QApplication a(argc, argv);

	QFont font;
	if(font.fromString(Custom().getFont()))
		qApp->setFont(font);

	auto lang = Custom().getLanguage();
	QTranslator translator;
	if(lang != "en_US" && translator.load(QCoreApplication::applicationDirPath()+"/languages/"+lang+".qm"))
		qApp->installTranslator(&translator);

	KaminecLauncher w;
	w.show();

	return a.exec();
}
