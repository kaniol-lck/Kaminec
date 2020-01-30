/********************************************************************************
** Form generated from reading UI file 'startgametab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTGAMETAB_H
#define UI_STARTGAMETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartGameTab
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *start_pb;

    void setupUi(QWidget *StartGameTab)
    {
        if (StartGameTab->objectName().isEmpty())
            StartGameTab->setObjectName(QString::fromUtf8("StartGameTab"));
        StartGameTab->resize(800, 400);
        StartGameTab->setWindowTitle(QString::fromUtf8("Form"));
        StartGameTab->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(StartGameTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 323, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        start_pb = new QPushButton(StartGameTab);
        start_pb->setObjectName(QString::fromUtf8("start_pb"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(start_pb->sizePolicy().hasHeightForWidth());
        start_pb->setSizePolicy(sizePolicy);
        start_pb->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setPointSize(17);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        font.setKerning(true);
        start_pb->setFont(font);
        start_pb->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: rgb(255, 255, 255);\n"
"	border: 0px;\n"
"	background-color: rgba(255, 255, 255, 63);\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgba(255, 255, 255, 79);\n"
"}\n"
"QPushButton:disabled{\n"
"	color: rgb(63, 63, 63);\n"
"	background-color: rgba(127, 127, 127, 191);\n"
"}"));

        verticalLayout->addWidget(start_pb);


        retranslateUi(StartGameTab);

        QMetaObject::connectSlotsByName(StartGameTab);
    } // setupUi

    void retranslateUi(QWidget *StartGameTab)
    {
        start_pb->setText(QApplication::translate("StartGameTab", "Launch", nullptr));
        Q_UNUSED(StartGameTab);
    } // retranslateUi

};

namespace Ui {
    class StartGameTab: public Ui_StartGameTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTGAMETAB_H
