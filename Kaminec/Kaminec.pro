#-------------------------------------------------
#
# Project created by QtCreator 2017-05-20T18:04:25
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kaminec
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
           UI/kamineclauncher.cpp \
           messager/profile.cpp \
           core/jsonmanager.cpp \
           core/game.cpp \
           messager/fileitem.cpp \
           LAminec/savesmanager.cpp \
    downloader/downloadmanagerplus.cpp \
    downloader/singledownload.cpp \
    core/auth.cpp \
    UI/preference.cpp \
    LAminec/profilemanager.cpp \
    core/assetmanager.cpp \
    downloader/gamedownload.cpp \
    UI/validatedialog.cpp \
    LAminec/modsmanager.cpp \
    assistance/logger.cpp \
    assistance/utility.cpp \
    core/GenericAuth.cpp \
    core/LaunchAuth.cpp \
    LAminec/ActiveAuth.cpp

HEADERS  += UI/kamineclauncher.h \
            messager/profile.h \
            core/gamemode.h \
            core/jsonmanager.h \
            core/game.h \
            messager/fileitem.h \
            LAminec/savesmanager.h \
    downloader/downloadmanagerplus.h \
    downloader/singledownload.h \
    core/auth.h \
    UI/preference.h \
    LAminec/profilemanager.h \
    core/assetmanager.h \
    downloader/gamedownload.h \
    UI/validatedialog.h \
    LAminec/modsmanager.h \
    assistance/utility.h \
    assistance/logger.h \
    core/GenericAuth.h \
    core/LaunchAuth.h \
    LAminec/ActiveAuth.h

FORMS    += UI/kamineclauncher.ui \
    UI/preference.ui \
    UI/validatedialog.ui

RESOURCES += \
	resources/background.qrc
