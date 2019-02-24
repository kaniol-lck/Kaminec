#include "UI/kamineclauncher.h"

#include <QApplication>
#include <QTranslator>

#include "assistance/Custom.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Kaniol");
	QCoreApplication::setApplicationName("KaminecLauncher");
	QApplication a(argc, argv);

	QFont font;
	if(font.fromString(Custom().getFont()))
		qApp->setFont(font);

	QString lang = Custom().getLanguage();
	QTranslator translator;
	if(translator.load(QCoreApplication::applicationDirPath()+"/languages/"+lang+".qm"))
		qApp->installTranslator(&translator);

	KaminecLauncher w;
	w.show();

	return a.exec();
}
