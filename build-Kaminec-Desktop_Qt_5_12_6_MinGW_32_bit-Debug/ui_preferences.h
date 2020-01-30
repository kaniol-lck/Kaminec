/********************************************************************************
** Form generated from reading UI file 'preferences.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCES_H
#define UI_PREFERENCES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_Preferences
{
public:
    QGridLayout *gridLayout_20;
    QDialogButtonBox *buttonBox;
    QTabWidget *preferencesSwitch;

    void setupUi(QDialog *Preferences)
    {
        if (Preferences->objectName().isEmpty())
            Preferences->setObjectName(QString::fromUtf8("Preferences"));
        Preferences->resize(493, 651);
        gridLayout_20 = new QGridLayout(Preferences);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        buttonBox = new QDialogButtonBox(Preferences);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_20->addWidget(buttonBox, 1, 0, 1, 1);

        preferencesSwitch = new QTabWidget(Preferences);
        preferencesSwitch->setObjectName(QString::fromUtf8("preferencesSwitch"));
        preferencesSwitch->setStyleSheet(QString::fromUtf8("QTabWidget::pane {border-top:0px solid #e8f3f9;background:  transparent; }\n"
"QTabBar::tab {min-height: 85px;min-width:40px;color: white;border: 0px solid;border-top-left-radius: 0px;border-top-right-radius: 0px;padding:3px;}\n"
"QTabBar::tab:!selected {color: gray; margin-top: 5px; background-color: rgb(255,255,255,200)}\n"
"QTabBar::tab:selected {color: black; border: 1px solid; background-color: rgb(255,255,255,255)}"));
        preferencesSwitch->setTabPosition(QTabWidget::West);
        preferencesSwitch->setTabShape(QTabWidget::Rounded);
        preferencesSwitch->setElideMode(Qt::ElideNone);
        preferencesSwitch->setUsesScrollButtons(true);
        preferencesSwitch->setDocumentMode(false);
        preferencesSwitch->setTabsClosable(false);
        preferencesSwitch->setMovable(false);
        preferencesSwitch->setTabBarAutoHide(false);

        gridLayout_20->addWidget(preferencesSwitch, 0, 0, 1, 1);


        retranslateUi(Preferences);
        QObject::connect(buttonBox, SIGNAL(accepted()), Preferences, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Preferences, SLOT(reject()));

        preferencesSwitch->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Preferences);
    } // setupUi

    void retranslateUi(QDialog *Preferences)
    {
        Preferences->setWindowTitle(QApplication::translate("Preferences", "Preferences", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Preferences: public Ui_Preferences {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCES_H
