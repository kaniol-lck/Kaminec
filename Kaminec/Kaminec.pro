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
	UI/preferences.cpp \
	UI/dialogs/accountdialog.cpp \
    assistance/Custom.cpp \
    assistance/Path.cpp \
	assistance/utility.cpp \
    check/Checker.cpp \
    check/CheckJson.cpp \
    check/CheckAssets.cpp \
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
    LAminec/ModsManager.cpp \
    LAminec/profileManager.cpp \
    LAminec/SavesManager.cpp \
    LAminec/LogCleaner.cpp \
    launch/Launcher.cpp \
	launch/LaunchJson.cpp \
	launch/Logger.cpp \
    messenger/Arguments.cpp \
    messenger/DownloadInfo.cpp \
	messenger/Profile.cpp \
	messenger/LaunchPack.cpp \
    messenger/Deficiency.cpp \
    messenger/CheckInfo.cpp \
    exception/Exception.cpp \
    exception/JsonParseException.cpp \
    check/CheckParser.cpp \
    launch/LaunchParser.cpp \
    assistance/PathReplacer.cpp \
    messenger/Account.cpp \
    LAminec/AccountPool.cpp \
    UI/dialogs/profiledialog.cpp \
    LAminec/GameVersionController.cpp \
    messenger/GameVersion.cpp \
    UI/preferences_tabs/javatab.cpp \
    UI/kamineclauncher_tabs/accounttab.cpp \
    UI/kamineclauncher_tabs/profiletab.cpp \
    UI/preferences_tabs/gametab.cpp \
    UI/preferences_tabs/pathtab.cpp \
    UI/kamineclauncher_tabs/startgametab.cpp \
    UI/downloadprogressdialog.cpp \
    UI/preferences_tabs/themetab.cpp \
    UI/preferences_tabs/launchertab.cpp \
    UI/kamineclauncher_tabs/gameoutputtab.cpp \
    download/VersionManifestDownload.cpp \
    download/DownloadPack.cpp \
    UI/dialogs/downloadgamedialog.cpp

HEADERS  += UI/kamineclauncher.h \
	UI/preferences.h \
	UI/dialogs/accountdialog.h \
    assistance/Custom.h \
    assistance/Gamemode.h \
    assistance/Path.h \
    assistance/systeminfo.h \
	assistance/utility.h \
    check/Checker.h \
    check/CheckJson.h \
    check/CheckAssets.h \
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
    LAminec/ModsManager.h \
    LAminec/ProfileManager.h \
    LAminec/SavesManager.h \
    LAminec/LogCleaner.h \
    launch/Launcher.h \
    launch/LaunchJson.h \
    launch/Logger.h \
    messenger/Arguments.h \
    messenger/DownloadInfo.h \
	messenger/Profile.h \
    messenger/LaunchPack.h \
    messenger/Deficiency.h \
    messenger/CheckInfo.h \
    exception/Exception.h \
    exception/JsonParseException.h \
    check/CheckParser.h \
    launch/LaunchParser.h \
    assistance/PathReplacer.h \
    messenger/Account.h \
    LAminec/AccountPool.h \
    exception/Exceptions.hpp \
    UI/dialogs/profiledialog.h \
    LAminec/GameVersionController.h \
    messenger/GameVersion.h \
    UI/preferences_tabs/javatab.h \
    UI/kamineclauncher_tabs/accounttab.h \
    UI/kamineclauncher_tabs/profiletab.h \
    UI/preferences_tabs/gametab.h \
    UI/preferences_tabs/pathtab.h \
    UI/kamineclauncher_tabs/startgametab.h \
    UI/downloadprogressdialog.h \
    UI/preferences_tabs/themetab.h \
    assistance/languages.hpp \
    UI/preferences_tabs/launchertab.h \
    UI/kamineclauncher_tabs/gameoutputtab.h \
    download/VersionManifestDownload.h \
    download/DownloadPack.h \
    UI/dialogs/downloadgamedialog.h

FORMS    += UI/kamineclauncher.ui \
    UI/preferences.ui \
    UI/dialogs/accountdialog.ui \
    UI/dialogs/profiledialog.ui \
    UI/preferences_tabs/javatab.ui \
    UI/kamineclauncher_tabs/accounttab.ui \
    UI/kamineclauncher_tabs/profiletab.ui \
    UI/preferences_tabs/gametab.ui \
    UI/preferences_tabs/pathtab.ui \
    UI/kamineclauncher_tabs/startgametab.ui \
    UI/downloadprogressdialog.ui \
    UI/preferences_tabs/themetab.ui \
    UI/preferences_tabs/launchertab.ui \
    UI/kamineclauncher_tabs/gameoutputtab.ui \
    UI/dialogs/downloadgamedialog.ui

TRANSLATIONS = ../Kaminec_translate/languages/en_US.ts \
			   ../Kaminec_translate/languages/zh_CN.ts

RESOURCES += \
	resources/background.qrc

RC_FILE = resources/Kaminec.rc

DISTFILES += \
    README.md

INCLUDEPATH += $$PWD/../3rd/quazip/include
LIBS += -L$$PWD/../3rd/quazip/lib/ -lquazip
