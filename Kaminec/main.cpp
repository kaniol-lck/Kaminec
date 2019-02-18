#include "UI/kamineclauncher.h"

#include <QApplication>

#include "assistance/Custom.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Kaniol");
	QCoreApplication::setApplicationName("KaminecLauncher");
	QFont font;
	if(font.fromString(Custom().getFont()))
		qApp->setFont(font);
	QApplication a(argc, argv);
	KaminecLauncher w;
	w.show();

	return a.exec();
}
