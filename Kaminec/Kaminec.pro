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
	UI/preference.cpp \
	UI/validatedialog.cpp \
    assistance/Custom.cpp \
    assistance/Path.cpp \
	assistance/utility.cpp \
    download/DownloadAssets.cpp \
	download/DownloadJson.cpp \
    download/GameDownload.cpp \
    kits/AssetKit/AssetKit.cpp \
    kits/AssetKit/AssetObject.cpp \
    kits/AuthKit/AuthKit.cpp \
    kits/AuthKit/AuthResponse.cpp \
    kits/DownloadKit/DownloadKit.cpp \
    kits/DownloadKit/SingleDownload.cpp \
    kits/JsonKit/AssetIndex.cpp \
    kits/JsonKit/GameCoreJar.cpp \
    kits/JsonKit/JsonKit.cpp \
    kits/JsonKit/Library.cpp \
    kits/Ruler/Rule.cpp \
    kits/Ruler/Ruler.cpp \
    LAminec/ActiveAuth.cpp \
    LAminec/ModsManager.cpp \
    LAminec/profileManager.cpp \
    LAminec/SavesManager.cpp \
    launch/GameParser.cpp \
    launch/LaunchAuth.cpp \
    launch/Launcher.cpp \
	launch/LaunchJson.cpp \
	launch/Logger.cpp \
    messager/Arguments.cpp \
    messager/FileItem.cpp \
	messager/Profile.cpp \
	messager/LaunchPack.cpp \
    exception/Exception.cpp \
    exception/FileNotFoundException.cpp \
    exception/JsonParseException.cpp \
    exception/DownloadException.cpp \
    exception/InvalidAccountException.cpp \
    exception/FileOpenException.cpp \
    LAminec/LogCleaner.cpp

HEADERS  += UI/kamineclauncher.h \
	UI/preference.h \
	UI/validatedialog.h \
    assistance/Custom.h \
    assistance/Gamemode.h \
    assistance/Path.h \
    assistance/systeminfo.h \
	assistance/utility.h \
    download/DownloadAssets.h \
	download/DownloadJson.h \
    download/GameDownload.h \
    kits/AssetKit/AssetKit.h \
    kits/AssetKit/AssetObject.h \
    kits/AuthKit/AuthKit.h \
    kits/AuthKit/AuthResponse.h \
    kits/DownloadKit/DownloadKit.h \
    kits/DownloadKit/SingleDownload.h \
    kits/JsonKit/AssetIndex.h \
    kits/JsonKit/GameCoreJar.h \
    kits/JsonKit/JsonKit.h \
    kits/JsonKit/Library.h \
    kits/Ruler/Rule.h \
    kits/Ruler/Ruler.h \
    LAminec/ActiveAuth.h \
    LAminec/ModsManager.h \
    LAminec/ProfileManager.h \
    LAminec/SavesManager.h \
    launch/GameParser.h \
    launch/LaunchAuth.h \
    launch/Launcher.h \
    launch/LaunchJson.h \
    launch/Logger.h \
    messager/Arguments.h \
    messager/FileItem.h \
	messager/Profile.h \
    messager/LaunchPack.h \
    exception/Exception.h \
    exception/FileNotFoundException.h \
    exception/JsonParseException.h \
    exception/DownloadException.h \
    exception/InvalidAccountException.h \
    exception/FileOpenException.h \
    assistance/Exceptions.h \
    LAminec/LogCleaner.h

FORMS    += UI/kamineclauncher.ui \
    UI/preference.ui \
    UI/validatedialog.ui

RESOURCES += \
	resources/background.qrc

RC_FILE = resources/icon.rc

DISTFILES += \
    README.md

INCLUDEPATH += $$PWD/../3rd/quazip/include
LIBS += -L$$PWD/../3rd/quazip/lib/ -lquazip
