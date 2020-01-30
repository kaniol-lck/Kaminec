/********************************************************************************
** Form generated from reading UI file 'profiletab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILETAB_H
#define UI_PROFILETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfileTab
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *profiles_tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *addProfile_pb;
    QPushButton *setProfileActive_pb;
    QPushButton *deleteProfile_pb;
    QPushButton *fixProfile_pb;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ProfileTab)
    {
        if (ProfileTab->objectName().isEmpty())
            ProfileTab->setObjectName(QString::fromUtf8("ProfileTab"));
        ProfileTab->resize(800, 400);
        ProfileTab->setWindowTitle(QString::fromUtf8("Form"));
        horizontalLayout = new QHBoxLayout(ProfileTab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        profiles_tableView = new QTableView(ProfileTab);
        profiles_tableView->setObjectName(QString::fromUtf8("profiles_tableView"));
        QFont font;
        font.setPointSize(11);
        profiles_tableView->setFont(font);
        profiles_tableView->setStyleSheet(QString::fromUtf8("QTableView {\n"
"    color: rgb(255, 255, 255);\n"
"	background-color: rgba(255, 255, 255, 63);\n"
"	alternate-background-color: rgba(191, 191, 191, 63);\n"
"    selection-color: rgb(0, 0, 0);\n"
"	selection-background-color: rgba(255, 255, 255, 191);\n"
"	border: none;\n"
"}\n"
"\n"
"QHeaderView {\n"
"	color: rgba(0, 0, 0, 255);\n"
"	background-color: rgba(255, 255, 255, 255);\n"
"    border: 1px;\n"
"	min-height: 40px;\n"
"	border-bottom: 1px solid rgba(191, 191, 191, 127);\n"
"}\n"
"\n"
""));
        profiles_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        profiles_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        profiles_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        profiles_tableView->setShowGrid(false);
        profiles_tableView->setSortingEnabled(true);
        profiles_tableView->horizontalHeader()->setHighlightSections(false);
        profiles_tableView->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(profiles_tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addProfile_pb = new QPushButton(ProfileTab);
        addProfile_pb->setObjectName(QString::fromUtf8("addProfile_pb"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addProfile_pb->sizePolicy().hasHeightForWidth());
        addProfile_pb->setSizePolicy(sizePolicy);
        addProfile_pb->setMinimumSize(QSize(120, 40));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        addProfile_pb->setFont(font1);
        addProfile_pb->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        verticalLayout->addWidget(addProfile_pb);

        setProfileActive_pb = new QPushButton(ProfileTab);
        setProfileActive_pb->setObjectName(QString::fromUtf8("setProfileActive_pb"));
        sizePolicy.setHeightForWidth(setProfileActive_pb->sizePolicy().hasHeightForWidth());
        setProfileActive_pb->setSizePolicy(sizePolicy);
        setProfileActive_pb->setMinimumSize(QSize(120, 40));
        setProfileActive_pb->setFont(font1);
        setProfileActive_pb->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        verticalLayout->addWidget(setProfileActive_pb);

        deleteProfile_pb = new QPushButton(ProfileTab);
        deleteProfile_pb->setObjectName(QString::fromUtf8("deleteProfile_pb"));
        deleteProfile_pb->setMinimumSize(QSize(0, 40));
        deleteProfile_pb->setFont(font1);
        deleteProfile_pb->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        verticalLayout->addWidget(deleteProfile_pb);

        fixProfile_pb = new QPushButton(ProfileTab);
        fixProfile_pb->setObjectName(QString::fromUtf8("fixProfile_pb"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fixProfile_pb->sizePolicy().hasHeightForWidth());
        fixProfile_pb->setSizePolicy(sizePolicy1);
        fixProfile_pb->setMinimumSize(QSize(0, 40));
        fixProfile_pb->setFont(font1);
        fixProfile_pb->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        verticalLayout->addWidget(fixProfile_pb);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(ProfileTab);

        QMetaObject::connectSlotsByName(ProfileTab);
    } // setupUi

    void retranslateUi(QWidget *ProfileTab)
    {
        addProfile_pb->setText(QApplication::translate("ProfileTab", "Add", nullptr));
        setProfileActive_pb->setText(QApplication::translate("ProfileTab", "Set Active", nullptr));
        deleteProfile_pb->setText(QApplication::translate("ProfileTab", "Delete", nullptr));
        fixProfile_pb->setText(QApplication::translate("ProfileTab", "Fix", nullptr));
        Q_UNUSED(ProfileTab);
    } // retranslateUi

};

namespace Ui {
    class ProfileTab: public Ui_ProfileTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILETAB_H
