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
           messager/fileitem.cpp \
           LAminec/savesmanager.cpp \
    downloader/downloadmanagerplus.cpp \
    downloader/singledownload.cpp \
    UI/preference.cpp \
    LAminec/profilemanager.cpp \
    downloader/gamedownload.cpp \
    UI/validatedialog.cpp \
    LAminec/modsmanager.cpp \
    assistance/logger.cpp \
    assistance/utility.cpp \
	core/auth/LaunchAuth.cpp \
    LAminec/ActiveAuth.cpp \
    core/Path.cpp \
	core/json/Library.cpp \
    core/Ruler.cpp \
    core/NewGame.cpp \
    core/Arguments.cpp \
    core/json/LaunchJson.cpp \
    core/json/AssetIndex.cpp \
    core/json/DownloadJson.cpp \
    core/json/JsonKit.cpp \
    core/json/GameCoreJar.cpp \
    core/auth/AuthKit.cpp \
    core/json/Object.cpp \
    core/json/AssetsKit.cpp \
    core/json/DownloadAssets.cpp

HEADERS  += UI/kamineclauncher.h \
            messager/profile.h \
            core/gamemode.h \
            messager/fileitem.h \
            LAminec/savesmanager.h \
    downloader/downloadmanagerplus.h \
    downloader/singledownload.h \
    UI/preference.h \
    LAminec/profilemanager.h \
    downloader/gamedownload.h \
    UI/validatedialog.h \
    LAminec/modsmanager.h \
    assistance/utility.h \
    assistance/logger.h \
	core/auth/LaunchAuth.h \
    LAminec/ActiveAuth.h \
    assistance/systeminfo.h \
    core/Path.h \
	core/json/Library.h \
    core/Ruler.h \
    core/NewGame.h \
    core/Arguments.h \
    core/json/LaunchJson.h \
    core/json/AssetIndex.h \
    core/json/DownloadJson.h \
    core/json/JsonKit.h \
    core/json/GameCoreJar.h \
    core/auth/AuthKit.h \
    core/json/Object.h \
    core/json/AssetsKit.h \
    core/json/DownloadAssets.h

FORMS    += UI/kamineclauncher.ui \
    UI/preference.ui \
    UI/validatedialog.ui

RESOURCES += \
	resources/background.qrc

RC_FILE = resources/icon.rc
