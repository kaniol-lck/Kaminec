/********************************************************************************
** Form generated from reading UI file 'gametab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMETAB_H
#define UI_GAMETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameTab
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *fullScreen_checkBox;
    QGroupBox *customizeResolution_gb;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *width_label;
    QSpinBox *width_sb;
    QHBoxLayout *horizontalLayout_6;
    QLabel *height_label;
    QSpinBox *height_sb;
    QFrame *line_3;
    QGroupBox *serverMode_gb;
    QGridLayout *gridLayout_10;
    QLabel *ip_label;
    QLineEdit *ip_le;
    QLabel *port_label;
    QLineEdit *port_le;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *GameTab)
    {
        if (GameTab->objectName().isEmpty())
            GameTab->setObjectName(QString::fromUtf8("GameTab"));
        GameTab->resize(400, 600);
        GameTab->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(GameTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        fullScreen_checkBox = new QCheckBox(GameTab);
        fullScreen_checkBox->setObjectName(QString::fromUtf8("fullScreen_checkBox"));

        verticalLayout->addWidget(fullScreen_checkBox);

        customizeResolution_gb = new QGroupBox(GameTab);
        customizeResolution_gb->setObjectName(QString::fromUtf8("customizeResolution_gb"));
        customizeResolution_gb->setCheckable(true);
        customizeResolution_gb->setChecked(false);
        horizontalLayout = new QHBoxLayout(customizeResolution_gb);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        width_label = new QLabel(customizeResolution_gb);
        width_label->setObjectName(QString::fromUtf8("width_label"));

        horizontalLayout_3->addWidget(width_label);

        width_sb = new QSpinBox(customizeResolution_gb);
        width_sb->setObjectName(QString::fromUtf8("width_sb"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(width_sb->sizePolicy().hasHeightForWidth());
        width_sb->setSizePolicy(sizePolicy);
        width_sb->setMaximum(999999999);

        horizontalLayout_3->addWidget(width_sb);


        horizontalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        height_label = new QLabel(customizeResolution_gb);
        height_label->setObjectName(QString::fromUtf8("height_label"));

        horizontalLayout_6->addWidget(height_label);

        height_sb = new QSpinBox(customizeResolution_gb);
        height_sb->setObjectName(QString::fromUtf8("height_sb"));
        sizePolicy.setHeightForWidth(height_sb->sizePolicy().hasHeightForWidth());
        height_sb->setSizePolicy(sizePolicy);
        height_sb->setMaximum(999999999);

        horizontalLayout_6->addWidget(height_sb);


        horizontalLayout->addLayout(horizontalLayout_6);


        verticalLayout->addWidget(customizeResolution_gb);

        line_3 = new QFrame(GameTab);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        serverMode_gb = new QGroupBox(GameTab);
        serverMode_gb->setObjectName(QString::fromUtf8("serverMode_gb"));
        serverMode_gb->setCheckable(true);
        serverMode_gb->setChecked(false);
        gridLayout_10 = new QGridLayout(serverMode_gb);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        ip_label = new QLabel(serverMode_gb);
        ip_label->setObjectName(QString::fromUtf8("ip_label"));

        gridLayout_10->addWidget(ip_label, 0, 0, 1, 1);

        ip_le = new QLineEdit(serverMode_gb);
        ip_le->setObjectName(QString::fromUtf8("ip_le"));

        gridLayout_10->addWidget(ip_le, 0, 1, 1, 1);

        port_label = new QLabel(serverMode_gb);
        port_label->setObjectName(QString::fromUtf8("port_label"));

        gridLayout_10->addWidget(port_label, 0, 2, 1, 1);

        port_le = new QLineEdit(serverMode_gb);
        port_le->setObjectName(QString::fromUtf8("port_le"));

        gridLayout_10->addWidget(port_le, 0, 3, 1, 1);


        verticalLayout->addWidget(serverMode_gb);

        verticalSpacer_3 = new QSpacerItem(17, 405, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

#ifndef QT_NO_SHORTCUT
        width_label->setBuddy(width_sb);
        height_label->setBuddy(height_sb);
        ip_label->setBuddy(ip_le);
        port_label->setBuddy(port_le);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(fullScreen_checkBox, customizeResolution_gb);
        QWidget::setTabOrder(customizeResolution_gb, width_sb);
        QWidget::setTabOrder(width_sb, height_sb);
        QWidget::setTabOrder(height_sb, serverMode_gb);
        QWidget::setTabOrder(serverMode_gb, ip_le);
        QWidget::setTabOrder(ip_le, port_le);

        retranslateUi(GameTab);

        QMetaObject::connectSlotsByName(GameTab);
    } // setupUi

    void retranslateUi(QWidget *GameTab)
    {
        fullScreen_checkBox->setText(QApplication::translate("GameTab", "Launch in Full Screen", nullptr));
        customizeResolution_gb->setTitle(QApplication::translate("GameTab", "Customize Resolution", nullptr));
        width_label->setText(QApplication::translate("GameTab", "Width:", nullptr));
        height_label->setText(QApplication::translate("GameTab", "Height:", nullptr));
        serverMode_gb->setTitle(QApplication::translate("GameTab", "Launch with Server", nullptr));
        ip_label->setText(QApplication::translate("GameTab", "IP:", nullptr));
        port_label->setText(QApplication::translate("GameTab", "Port:", nullptr));
        Q_UNUSED(GameTab);
    } // retranslateUi

};

namespace Ui {
    class GameTab: public Ui_GameTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMETAB_H
