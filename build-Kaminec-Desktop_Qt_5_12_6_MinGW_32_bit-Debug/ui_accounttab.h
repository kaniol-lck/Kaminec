/********************************************************************************
** Form generated from reading UI file 'accounttab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTTAB_H
#define UI_ACCOUNTTAB_H

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

class Ui_AccountTab
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *accounts_tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *addAccount_pb;
    QPushButton *setAccountActive_pb;
    QPushButton *deleteAccount_pb;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *AccountTab)
    {
        if (AccountTab->objectName().isEmpty())
            AccountTab->setObjectName(QString::fromUtf8("AccountTab"));
        AccountTab->resize(800, 400);
        AccountTab->setWindowTitle(QString::fromUtf8("Form"));
        horizontalLayout = new QHBoxLayout(AccountTab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        accounts_tableView = new QTableView(AccountTab);
        accounts_tableView->setObjectName(QString::fromUtf8("accounts_tableView"));
        accounts_tableView->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(11);
        accounts_tableView->setFont(font);
        accounts_tableView->setStyleSheet(QString::fromUtf8("QTableView {\n"
"    color: rgb(255, 255, 255);\n"
"	background-color: rgba(255, 255, 255, 0);\n"
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
        accounts_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        accounts_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        accounts_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        accounts_tableView->setShowGrid(false);
        accounts_tableView->setSortingEnabled(true);
        accounts_tableView->horizontalHeader()->setHighlightSections(false);
        accounts_tableView->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(accounts_tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addAccount_pb = new QPushButton(AccountTab);
        addAccount_pb->setObjectName(QString::fromUtf8("addAccount_pb"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addAccount_pb->sizePolicy().hasHeightForWidth());
        addAccount_pb->setSizePolicy(sizePolicy);
        addAccount_pb->setMinimumSize(QSize(120, 40));
        QFont font1;
        font1.setPointSize(14);
        addAccount_pb->setFont(font1);
        addAccount_pb->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        verticalLayout->addWidget(addAccount_pb);

        setAccountActive_pb = new QPushButton(AccountTab);
        setAccountActive_pb->setObjectName(QString::fromUtf8("setAccountActive_pb"));
        setAccountActive_pb->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(setAccountActive_pb->sizePolicy().hasHeightForWidth());
        setAccountActive_pb->setSizePolicy(sizePolicy1);
        setAccountActive_pb->setMinimumSize(QSize(120, 40));
        setAccountActive_pb->setFont(font1);
        setAccountActive_pb->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        verticalLayout->addWidget(setAccountActive_pb);

        deleteAccount_pb = new QPushButton(AccountTab);
        deleteAccount_pb->setObjectName(QString::fromUtf8("deleteAccount_pb"));
        deleteAccount_pb->setMinimumSize(QSize(0, 40));
        deleteAccount_pb->setFont(font1);
        deleteAccount_pb->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        verticalLayout->addWidget(deleteAccount_pb);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(AccountTab);

        QMetaObject::connectSlotsByName(AccountTab);
    } // setupUi

    void retranslateUi(QWidget *AccountTab)
    {
        addAccount_pb->setText(QApplication::translate("AccountTab", "Add", nullptr));
        setAccountActive_pb->setText(QApplication::translate("AccountTab", "Set Active", nullptr));
        deleteAccount_pb->setText(QApplication::translate("AccountTab", "Delete", nullptr));
        Q_UNUSED(AccountTab);
    } // retranslateUi

};

namespace Ui {
    class AccountTab: public Ui_AccountTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTTAB_H
