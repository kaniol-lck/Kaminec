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
           kamineclauncher.cpp \
           profile.cpp \
           jsonmanager.cpp \
           game.cpp \
           fileitem.cpp \
           savesmanager.cpp \
    downloadmanagerplus.cpp \
    singledownload.cpp \
    auth.cpp \
    preference.cpp \
    profilemanager.cpp \
    assetmanager.cpp \
    gamedownload.cpp \
    validatedialog.cpp \
    modsmanager.cpp \
    logger.cpp \
    utility.cpp

HEADERS  += kamineclauncher.h \
            profile.h \
            gamemode.h \
            jsonmanager.h \
            game.h \
            fileitem.h \
            savesmanager.h \
    downloadmanagerplus.h \
    singledownload.h \
    auth.h \
    preference.h \
    profilemanager.h \
    assetmanager.h \
    gamedownload.h \
    validatedialog.h \
    modsmanager.h \
    utility.h \
    logger.h

FORMS    += kamineclauncher.ui \
    preference.ui \
    validatedialog.ui

RESOURCES += \
    background.qrc
