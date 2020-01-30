/********************************************************************************
** Form generated from reading UI file 'profiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEDIALOG_H
#define UI_PROFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProfileDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *hint_label;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_16;
    QLabel *version_label;
    QLineEdit *profileName_le;
    QLabel *profileName_label;
    QLabel *gameDir_label;
    QHBoxLayout *horizontalLayout_9;
    QComboBox *version_cb;
    QPushButton *check_pb;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *gameDir_le;
    QPushButton *gameDir_showPb;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ProfileDialog)
    {
        if (ProfileDialog->objectName().isEmpty())
            ProfileDialog->setObjectName(QString::fromUtf8("ProfileDialog"));
        ProfileDialog->resize(360, 175);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProfileDialog->sizePolicy().hasHeightForWidth());
        ProfileDialog->setSizePolicy(sizePolicy);
        ProfileDialog->setWindowTitle(QString::fromUtf8("Dialog"));
        verticalLayout = new QVBoxLayout(ProfileDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        hint_label = new QLabel(ProfileDialog);
        hint_label->setObjectName(QString::fromUtf8("hint_label"));
        QFont font;
        font.setPointSize(19);
        font.setBold(true);
        font.setWeight(75);
        hint_label->setFont(font);
        hint_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(hint_label);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        gridLayout_16 = new QGridLayout();
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        version_label = new QLabel(ProfileDialog);
        version_label->setObjectName(QString::fromUtf8("version_label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(version_label->sizePolicy().hasHeightForWidth());
        version_label->setSizePolicy(sizePolicy1);
        version_label->setMaximumSize(QSize(100, 16777215));
        version_label->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(version_label, 1, 0, 1, 2);

        profileName_le = new QLineEdit(ProfileDialog);
        profileName_le->setObjectName(QString::fromUtf8("profileName_le"));

        gridLayout_16->addWidget(profileName_le, 0, 2, 1, 1);

        profileName_label = new QLabel(ProfileDialog);
        profileName_label->setObjectName(QString::fromUtf8("profileName_label"));
        sizePolicy1.setHeightForWidth(profileName_label->sizePolicy().hasHeightForWidth());
        profileName_label->setSizePolicy(sizePolicy1);
        profileName_label->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(profileName_label, 0, 0, 1, 2);

        gameDir_label = new QLabel(ProfileDialog);
        gameDir_label->setObjectName(QString::fromUtf8("gameDir_label"));
        sizePolicy1.setHeightForWidth(gameDir_label->sizePolicy().hasHeightForWidth());
        gameDir_label->setSizePolicy(sizePolicy1);
        gameDir_label->setMaximumSize(QSize(100, 16777215));
        gameDir_label->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(gameDir_label, 2, 0, 1, 2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        version_cb = new QComboBox(ProfileDialog);
        version_cb->setObjectName(QString::fromUtf8("version_cb"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(version_cb->sizePolicy().hasHeightForWidth());
        version_cb->setSizePolicy(sizePolicy2);
        version_cb->setStyleSheet(QString::fromUtf8(""));
        version_cb->setDuplicatesEnabled(false);
        version_cb->setFrame(true);

        horizontalLayout_9->addWidget(version_cb);

        check_pb = new QPushButton(ProfileDialog);
        check_pb->setObjectName(QString::fromUtf8("check_pb"));

        horizontalLayout_9->addWidget(check_pb);


        gridLayout_16->addLayout(horizontalLayout_9, 1, 2, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        gameDir_le = new QLineEdit(ProfileDialog);
        gameDir_le->setObjectName(QString::fromUtf8("gameDir_le"));

        horizontalLayout_10->addWidget(gameDir_le);

        gameDir_showPb = new QPushButton(ProfileDialog);
        gameDir_showPb->setObjectName(QString::fromUtf8("gameDir_showPb"));
        gameDir_showPb->setAutoFillBackground(false);
        gameDir_showPb->setStyleSheet(QString::fromUtf8(""));
        gameDir_showPb->setFlat(false);

        horizontalLayout_10->addWidget(gameDir_showPb);


        gridLayout_16->addLayout(horizontalLayout_10, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_16);

        buttonBox = new QDialogButtonBox(ProfileDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        version_label->setBuddy(version_cb);
        profileName_label->setBuddy(profileName_le);
        gameDir_label->setBuddy(gameDir_le);
#endif // QT_NO_SHORTCUT

        retranslateUi(ProfileDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), ProfileDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ProfileDialog);
    } // setupUi

    void retranslateUi(QDialog *ProfileDialog)
    {
        hint_label->setText(QApplication::translate("ProfileDialog", "New Profile", nullptr));
        version_label->setText(QApplication::translate("ProfileDialog", "Exsited Version:", nullptr));
        profileName_label->setText(QApplication::translate("ProfileDialog", "Name:", nullptr));
        gameDir_label->setText(QApplication::translate("ProfileDialog", "Game Directory:", nullptr));
        check_pb->setText(QApplication::translate("ProfileDialog", "Check", nullptr));
        gameDir_showPb->setText(QApplication::translate("ProfileDialog", "...", nullptr));
        Q_UNUSED(ProfileDialog);
    } // retranslateUi

};

namespace Ui {
    class ProfileDialog: public Ui_ProfileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEDIALOG_H
