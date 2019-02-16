#include "UI/kamineclauncher.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Kaniol");
	QCoreApplication::setApplicationName("KaminecLauncher");
	QApplication a(argc, argv);
	KaminecLauncher w;
	w.show();

	return a.exec();
}
