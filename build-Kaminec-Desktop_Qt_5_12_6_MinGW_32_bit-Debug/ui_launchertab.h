/********************************************************************************
** Form generated from reading UI file 'launchertab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAUNCHERTAB_H
#define UI_LAUNCHERTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LauncherTab
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *logNumber_label;
    QLabel *logTip_label;
    QSpinBox *logNumber_spinBox;
    QHBoxLayout *horizontalLayout;
    QLabel *lang_label;
    QComboBox *lang_cb;
    QCheckBox *bmclapi_checkBox;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *LauncherTab)
    {
        if (LauncherTab->objectName().isEmpty())
            LauncherTab->setObjectName(QString::fromUtf8("LauncherTab"));
        LauncherTab->resize(400, 600);
        LauncherTab->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout_2 = new QVBoxLayout(LauncherTab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(LauncherTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
#ifndef QT_NO_WHATSTHIS
        groupBox->setWhatsThis(QString::fromUtf8(""));
#endif // QT_NO_WHATSTHIS
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        logNumber_label = new QLabel(groupBox);
        logNumber_label->setObjectName(QString::fromUtf8("logNumber_label"));

        horizontalLayout_4->addWidget(logNumber_label);

        logTip_label = new QLabel(groupBox);
        logTip_label->setObjectName(QString::fromUtf8("logTip_label"));

        horizontalLayout_4->addWidget(logTip_label);

        logNumber_spinBox = new QSpinBox(groupBox);
        logNumber_spinBox->setObjectName(QString::fromUtf8("logNumber_spinBox"));
        logNumber_spinBox->setMinimum(-1);

        horizontalLayout_4->addWidget(logNumber_spinBox);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lang_label = new QLabel(LauncherTab);
        lang_label->setObjectName(QString::fromUtf8("lang_label"));

        horizontalLayout->addWidget(lang_label);

        lang_cb = new QComboBox(LauncherTab);
        lang_cb->setObjectName(QString::fromUtf8("lang_cb"));
#ifndef QT_NO_WHATSTHIS
        lang_cb->setWhatsThis(QString::fromUtf8(""));
#endif // QT_NO_WHATSTHIS

        horizontalLayout->addWidget(lang_cb);


        verticalLayout_2->addLayout(horizontalLayout);

        bmclapi_checkBox = new QCheckBox(LauncherTab);
        bmclapi_checkBox->setObjectName(QString::fromUtf8("bmclapi_checkBox"));

        verticalLayout_2->addWidget(bmclapi_checkBox);

        verticalSpacer_4 = new QSpacerItem(20, 507, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

#ifndef QT_NO_SHORTCUT
        logNumber_label->setBuddy(logNumber_spinBox);
        lang_label->setBuddy(lang_cb);
#endif // QT_NO_SHORTCUT

        retranslateUi(LauncherTab);

        QMetaObject::connectSlotsByName(LauncherTab);
    } // setupUi

    void retranslateUi(QWidget *LauncherTab)
    {
        groupBox->setTitle(QApplication::translate("LauncherTab", "Logger", nullptr));
        logNumber_label->setText(QApplication::translate("LauncherTab", "Log File Limit:", nullptr));
        logTip_label->setText(QApplication::translate("LauncherTab", "No Limit", nullptr));
        lang_label->setText(QApplication::translate("LauncherTab", "Language:", nullptr));
        bmclapi_checkBox->setText(QApplication::translate("LauncherTab", "Use BMCLAPI to download game", nullptr));
        Q_UNUSED(LauncherTab);
    } // retranslateUi

};

namespace Ui {
    class LauncherTab: public Ui_LauncherTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAUNCHERTAB_H
