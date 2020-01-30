/********************************************************************************
** Form generated from reading UI file 'gameoutputtab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEOUTPUTTAB_H
#define UI_GAMEOUTPUTTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameOutputTab
{
public:
    QGridLayout *gridLayout;
    QListView *output_listView;

    void setupUi(QWidget *GameOutputTab)
    {
        if (GameOutputTab->objectName().isEmpty())
            GameOutputTab->setObjectName(QString::fromUtf8("GameOutputTab"));
        GameOutputTab->resize(800, 400);
        gridLayout = new QGridLayout(GameOutputTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        output_listView = new QListView(GameOutputTab);
        output_listView->setObjectName(QString::fromUtf8("output_listView"));
        output_listView->setStyleSheet(QString::fromUtf8("QListView {\n"
"    color: rgb(255, 255, 255);\n"
"	background-color: rgba(255, 255, 255, 31);\n"
"    selection-color: rgb(0, 0, 0);\n"
"	selection-background-color: rgba(255, 255, 255, 191);\n"
"	border: none;\n"
"}\n"
""));

        gridLayout->addWidget(output_listView, 0, 0, 1, 1);


        retranslateUi(GameOutputTab);

        QMetaObject::connectSlotsByName(GameOutputTab);
    } // setupUi

    void retranslateUi(QWidget *GameOutputTab)
    {
        GameOutputTab->setWindowTitle(QApplication::translate("GameOutputTab", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameOutputTab: public Ui_GameOutputTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOUTPUTTAB_H
