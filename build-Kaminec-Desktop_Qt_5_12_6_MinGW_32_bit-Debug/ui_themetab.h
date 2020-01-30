/********************************************************************************
** Form generated from reading UI file 'themetab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THEMETAB_H
#define UI_THEMETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThemeTab
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *font_label;
    QFontComboBox *fontComboBox;
    QSpinBox *font_spinBox;
    QPushButton *font_pb;
    QLabel *background_label;
    QPushButton *background_showPb;
    QLineEdit *background_le;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ThemeTab)
    {
        if (ThemeTab->objectName().isEmpty())
            ThemeTab->setObjectName(QString::fromUtf8("ThemeTab"));
        ThemeTab->resize(422, 600);
        ThemeTab->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(ThemeTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        font_label = new QLabel(ThemeTab);
        font_label->setObjectName(QString::fromUtf8("font_label"));

        gridLayout->addWidget(font_label, 0, 0, 1, 1);

        fontComboBox = new QFontComboBox(ThemeTab);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));
        fontComboBox->setEditable(false);

        gridLayout->addWidget(fontComboBox, 0, 1, 1, 2);

        font_spinBox = new QSpinBox(ThemeTab);
        font_spinBox->setObjectName(QString::fromUtf8("font_spinBox"));
        font_spinBox->setMinimum(6);
        font_spinBox->setMaximum(72);
        font_spinBox->setValue(9);

        gridLayout->addWidget(font_spinBox, 0, 3, 1, 1);

        font_pb = new QPushButton(ThemeTab);
        font_pb->setObjectName(QString::fromUtf8("font_pb"));

        gridLayout->addWidget(font_pb, 0, 4, 1, 1);

        background_label = new QLabel(ThemeTab);
        background_label->setObjectName(QString::fromUtf8("background_label"));

        gridLayout->addWidget(background_label, 1, 0, 1, 1);

        background_showPb = new QPushButton(ThemeTab);
        background_showPb->setObjectName(QString::fromUtf8("background_showPb"));

        gridLayout->addWidget(background_showPb, 1, 4, 1, 1);

        background_le = new QLineEdit(ThemeTab);
        background_le->setObjectName(QString::fromUtf8("background_le"));

        gridLayout->addWidget(background_le, 1, 1, 1, 3);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 510, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

#ifndef QT_NO_SHORTCUT
        font_label->setBuddy(fontComboBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(fontComboBox, font_pb);

        retranslateUi(ThemeTab);

        QMetaObject::connectSlotsByName(ThemeTab);
    } // setupUi

    void retranslateUi(QWidget *ThemeTab)
    {
        font_label->setText(QApplication::translate("ThemeTab", "Font:", nullptr));
        font_pb->setText(QApplication::translate("ThemeTab", "Choose Font...", nullptr));
        background_label->setText(QApplication::translate("ThemeTab", "Background:", nullptr));
        background_showPb->setText(QApplication::translate("ThemeTab", "...", nullptr));
        Q_UNUSED(ThemeTab);
    } // retranslateUi

};

namespace Ui {
    class ThemeTab: public Ui_ThemeTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THEMETAB_H
