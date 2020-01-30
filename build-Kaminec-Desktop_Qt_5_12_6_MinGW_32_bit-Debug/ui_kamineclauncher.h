/********************************************************************************
** Form generated from reading UI file 'kamineclauncher.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KAMINECLAUNCHER_H
#define UI_KAMINECLAUNCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KaminecLauncher
{
public:
    QAction *action_preferences;
    QAction *action_Download_Progress;
    QAction *actionDownload_Game;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *moduleSwitch;
    QMenuBar *menuBar;
    QMenu *menu_Tools;
    QMenu *menu_Download;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *KaminecLauncher)
    {
        if (KaminecLauncher->objectName().isEmpty())
            KaminecLauncher->setObjectName(QString::fromUtf8("KaminecLauncher"));
        KaminecLauncher->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KaminecLauncher->sizePolicy().hasHeightForWidth());
        KaminecLauncher->setSizePolicy(sizePolicy);
        KaminecLauncher->setStyleSheet(QString::fromUtf8(""));
        action_preferences = new QAction(KaminecLauncher);
        action_preferences->setObjectName(QString::fromUtf8("action_preferences"));
        action_Download_Progress = new QAction(KaminecLauncher);
        action_Download_Progress->setObjectName(QString::fromUtf8("action_Download_Progress"));
        actionDownload_Game = new QAction(KaminecLauncher);
        actionDownload_Game->setObjectName(QString::fromUtf8("actionDownload_Game"));
        centralWidget = new QWidget(KaminecLauncher);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        moduleSwitch = new QTabWidget(centralWidget);
        moduleSwitch->setObjectName(QString::fromUtf8("moduleSwitch"));
        QFont font;
        font.setPointSize(12);
        moduleSwitch->setFont(font);
        moduleSwitch->setAutoFillBackground(false);
        moduleSwitch->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
"	border: 1px black;\n"
"	background: rgba(255, 255, 255, 15); \n"
"}\n"
"\n"
"QTabBar::tab {\n"
"	min-width:100px;\n"
"	min-height:40px;\n"
"	border: 0px solid;\n"
"	padding:3px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"	color: white; \n"
"	margin-top: 5px;\n"
"	margin-left: 5px;\n"
"	background-color: rgb(255,255,255,0);\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"	color: white; \n"
"	margin-left: 5px;\n"
"	background-color: rgb(255,255,255,15);\n"
"}"));
        moduleSwitch->setTabPosition(QTabWidget::North);
        moduleSwitch->setTabShape(QTabWidget::Rounded);
        moduleSwitch->setElideMode(Qt::ElideNone);
        moduleSwitch->setTabsClosable(false);
        moduleSwitch->setMovable(false);
        moduleSwitch->setTabBarAutoHide(false);

        gridLayout->addWidget(moduleSwitch, 0, 0, 1, 1);

        KaminecLauncher->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(KaminecLauncher);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 22));
        menuBar->setStyleSheet(QString::fromUtf8("QToolBar {\n"
"    background-color: rgba(63, 63, 63, 191);\n"
"    border: none;\n"
"    padding: 1px;\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QToolBar:handle {\n"
"    background: white;\n"
"    border-left: 1px dotted grey;\n"
"    color: rgba(63, 63, 63, 191);\n"
"}\n"
"\n"
"QToolBar::separator {\n"
"    width: 6px;\n"
"    background-color: #222222;\n"
"}\n"
""));
        menu_Tools = new QMenu(menuBar);
        menu_Tools->setObjectName(QString::fromUtf8("menu_Tools"));
        menu_Download = new QMenu(menuBar);
        menu_Download->setObjectName(QString::fromUtf8("menu_Download"));
        KaminecLauncher->setMenuBar(menuBar);
        mainToolBar = new QToolBar(KaminecLauncher);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setStyleSheet(QString::fromUtf8("QToolBar {\n"
"    background-color: rgba(191, 191, 191, 127);\n"
"    border: none;\n"
"    padding: 1px;\n"
"}\n"
"\n"
"QToolBar:handle {\n"
"    background: rgba(191, 191, 191, 191);\n"
"    border-left: 1px dotted grey;\n"
"    color: rgba(191, 191, 191, 127);\n"
"}\n"
"\n"
"QToolBar::separator {\n"
"    width: 6px;\n"
"    background-color: #222222;\n"
"}\n"
""));
        mainToolBar->setOrientation(Qt::Vertical);
        mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        KaminecLauncher->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(KaminecLauncher);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setStyleSheet(QString::fromUtf8("background-color: rgba(63, 63, 63, 127);"));
        KaminecLauncher->setStatusBar(statusBar);

        menuBar->addAction(menu_Tools->menuAction());
        menuBar->addAction(menu_Download->menuAction());
        menu_Tools->addSeparator();
        menu_Tools->addAction(action_Download_Progress);
        menu_Tools->addSeparator();
        menu_Tools->addAction(action_preferences);
        menu_Download->addAction(actionDownload_Game);
        mainToolBar->addAction(action_Download_Progress);
        mainToolBar->addAction(action_preferences);

        retranslateUi(KaminecLauncher);

        moduleSwitch->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(KaminecLauncher);
    } // setupUi

    void retranslateUi(QMainWindow *KaminecLauncher)
    {
        KaminecLauncher->setWindowTitle(QApplication::translate("KaminecLauncher", "KaminecLauncher", nullptr));
        action_preferences->setText(QApplication::translate("KaminecLauncher", "&Preferences", nullptr));
#ifndef QT_NO_TOOLTIP
        action_preferences->setToolTip(QApplication::translate("KaminecLauncher", "Preferences", nullptr));
#endif // QT_NO_TOOLTIP
        action_Download_Progress->setText(QApplication::translate("KaminecLauncher", "&Download Progress", nullptr));
        actionDownload_Game->setText(QApplication::translate("KaminecLauncher", "Download Game", nullptr));
        menu_Tools->setTitle(QApplication::translate("KaminecLauncher", "&Tools", nullptr));
        menu_Download->setTitle(QApplication::translate("KaminecLauncher", "&Download", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KaminecLauncher: public Ui_KaminecLauncher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KAMINECLAUNCHER_H
