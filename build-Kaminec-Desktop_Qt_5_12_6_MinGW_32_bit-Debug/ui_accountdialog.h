/********************************************************************************
** Form generated from reading UI file 'accountdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTDIALOG_H
#define UI_ACCOUNTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AccountDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *hint_label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *certified_rb;
    QRadioButton *uncertified_rb;
    QGridLayout *gridLayout;
    QLabel *email_label;
    QLineEdit *email_le;
    QLabel *password_label;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *password_le;
    QPushButton *showPassword_pb;
    QLabel *playername_label;
    QLineEdit *playername_le;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AccountDialog)
    {
        if (AccountDialog->objectName().isEmpty())
            AccountDialog->setObjectName(QString::fromUtf8("AccountDialog"));
        AccountDialog->resize(360, 243);
        AccountDialog->setWindowTitle(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(AccountDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        hint_label = new QLabel(AccountDialog);
        hint_label->setObjectName(QString::fromUtf8("hint_label"));
        QFont font;
        font.setPointSize(19);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        hint_label->setFont(font);
        hint_label->setLayoutDirection(Qt::LeftToRight);
        hint_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(hint_label);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        certified_rb = new QRadioButton(AccountDialog);
        certified_rb->setObjectName(QString::fromUtf8("certified_rb"));
        certified_rb->setChecked(true);

        horizontalLayout_2->addWidget(certified_rb);

        uncertified_rb = new QRadioButton(AccountDialog);
        uncertified_rb->setObjectName(QString::fromUtf8("uncertified_rb"));
        uncertified_rb->setChecked(false);

        horizontalLayout_2->addWidget(uncertified_rb);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        email_label = new QLabel(AccountDialog);
        email_label->setObjectName(QString::fromUtf8("email_label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(email_label->sizePolicy().hasHeightForWidth());
        email_label->setSizePolicy(sizePolicy);
        email_label->setMinimumSize(QSize(50, 0));

        gridLayout->addWidget(email_label, 1, 0, 1, 1);

        email_le = new QLineEdit(AccountDialog);
        email_le->setObjectName(QString::fromUtf8("email_le"));

        gridLayout->addWidget(email_le, 1, 1, 1, 2);

        password_label = new QLabel(AccountDialog);
        password_label->setObjectName(QString::fromUtf8("password_label"));

        gridLayout->addWidget(password_label, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        password_le = new QLineEdit(AccountDialog);
        password_le->setObjectName(QString::fromUtf8("password_le"));

        horizontalLayout_3->addWidget(password_le);

        showPassword_pb = new QPushButton(AccountDialog);
        showPassword_pb->setObjectName(QString::fromUtf8("showPassword_pb"));
        showPassword_pb->setCheckable(true);

        horizontalLayout_3->addWidget(showPassword_pb);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 2);

        playername_label = new QLabel(AccountDialog);
        playername_label->setObjectName(QString::fromUtf8("playername_label"));
        sizePolicy.setHeightForWidth(playername_label->sizePolicy().hasHeightForWidth());
        playername_label->setSizePolicy(sizePolicy);
        playername_label->setMinimumSize(QSize(50, 0));

        gridLayout->addWidget(playername_label, 3, 0, 1, 1);

        playername_le = new QLineEdit(AccountDialog);
        playername_le->setObjectName(QString::fromUtf8("playername_le"));

        gridLayout->addWidget(playername_le, 3, 1, 1, 2);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        buttonBox = new QDialogButtonBox(AccountDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        email_label->setBuddy(email_le);
        password_label->setBuddy(password_le);
        playername_label->setBuddy(playername_le);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(certified_rb, uncertified_rb);
        QWidget::setTabOrder(uncertified_rb, email_le);
        QWidget::setTabOrder(email_le, password_le);
        QWidget::setTabOrder(password_le, showPassword_pb);

        retranslateUi(AccountDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), AccountDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AccountDialog);
    } // setupUi

    void retranslateUi(QDialog *AccountDialog)
    {
        hint_label->setText(QApplication::translate("AccountDialog", "New Account", nullptr));
        certified_rb->setText(QApplication::translate("AccountDialog", "Certified", nullptr));
        uncertified_rb->setText(QApplication::translate("AccountDialog", "Uncertified", nullptr));
        email_label->setText(QApplication::translate("AccountDialog", "Email:", nullptr));
        password_label->setText(QApplication::translate("AccountDialog", "Password:", nullptr));
        showPassword_pb->setText(QApplication::translate("AccountDialog", "Show Password", nullptr));
        playername_label->setText(QApplication::translate("AccountDialog", "Playername:", nullptr));
        Q_UNUSED(AccountDialog);
    } // retranslateUi

};

namespace Ui {
    class AccountDialog: public Ui_AccountDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTDIALOG_H
