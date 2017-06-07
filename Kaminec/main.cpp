#include "kamineclauncher.h"
#include <QApplication>
#include "jsonmanager.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KaminecLauncher w;
    w.show();

    return a.exec();
}
