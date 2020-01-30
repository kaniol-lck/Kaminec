/********************************************************************************
** Form generated from reading UI file 'javatab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JAVATAB_H
#define UI_JAVATAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JavaTab
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *javaPath_label;
    QLineEdit *javaPath_le;
    QPushButton *autoJava_pb;
    QPushButton *javaPath_showPb;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *officialPolicy_rb;
    QRadioButton *KaminecPolicy_rb;
    QRadioButton *CustomPolicy_rb;
    QGroupBox *customJVMArgs_gb;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_7;
    QPushButton *removeArg_pushButton;
    QPushButton *addArg_pushButton;
    QListWidget *customJVMArgs_listWidget;
    QSpacerItem *verticalSpacer_5;
    QFrame *line_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *minMem_label;
    QSpinBox *minMem_sb;
    QHBoxLayout *horizontalLayout;
    QLabel *maxMem_label;
    QSpinBox *maxMem_sb;

    void setupUi(QWidget *JavaTab)
    {
        if (JavaTab->objectName().isEmpty())
            JavaTab->setObjectName(QString::fromUtf8("JavaTab"));
        JavaTab->resize(400, 600);
        JavaTab->setWindowTitle(QString::fromUtf8("Form"));
        gridLayout = new QGridLayout(JavaTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_5 = new QGroupBox(JavaTab);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout = new QVBoxLayout(groupBox_5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        javaPath_label = new QLabel(groupBox_5);
        javaPath_label->setObjectName(QString::fromUtf8("javaPath_label"));

        horizontalLayout_5->addWidget(javaPath_label);

        javaPath_le = new QLineEdit(groupBox_5);
        javaPath_le->setObjectName(QString::fromUtf8("javaPath_le"));

        horizontalLayout_5->addWidget(javaPath_le);

        autoJava_pb = new QPushButton(groupBox_5);
        autoJava_pb->setObjectName(QString::fromUtf8("autoJava_pb"));

        horizontalLayout_5->addWidget(autoJava_pb);

        javaPath_showPb = new QPushButton(groupBox_5);
        javaPath_showPb->setObjectName(QString::fromUtf8("javaPath_showPb"));

        horizontalLayout_5->addWidget(javaPath_showPb);


        verticalLayout->addLayout(horizontalLayout_5);

        groupBox_7 = new QGroupBox(groupBox_5);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setCheckable(false);
        horizontalLayout_3 = new QHBoxLayout(groupBox_7);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        officialPolicy_rb = new QRadioButton(groupBox_7);
        officialPolicy_rb->setObjectName(QString::fromUtf8("officialPolicy_rb"));

        horizontalLayout_3->addWidget(officialPolicy_rb);

        KaminecPolicy_rb = new QRadioButton(groupBox_7);
        KaminecPolicy_rb->setObjectName(QString::fromUtf8("KaminecPolicy_rb"));
        KaminecPolicy_rb->setChecked(true);

        horizontalLayout_3->addWidget(KaminecPolicy_rb);

        CustomPolicy_rb = new QRadioButton(groupBox_7);
        CustomPolicy_rb->setObjectName(QString::fromUtf8("CustomPolicy_rb"));

        horizontalLayout_3->addWidget(CustomPolicy_rb);


        verticalLayout->addWidget(groupBox_7);

        customJVMArgs_gb = new QGroupBox(groupBox_5);
        customJVMArgs_gb->setObjectName(QString::fromUtf8("customJVMArgs_gb"));
        customJVMArgs_gb->setCheckable(true);
        customJVMArgs_gb->setChecked(false);
        gridLayout_2 = new QGridLayout(customJVMArgs_gb);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        removeArg_pushButton = new QPushButton(customJVMArgs_gb);
        removeArg_pushButton->setObjectName(QString::fromUtf8("removeArg_pushButton"));

        gridLayout_7->addWidget(removeArg_pushButton, 3, 0, 1, 1);

        addArg_pushButton = new QPushButton(customJVMArgs_gb);
        addArg_pushButton->setObjectName(QString::fromUtf8("addArg_pushButton"));

        gridLayout_7->addWidget(addArg_pushButton, 2, 0, 1, 1);

        customJVMArgs_listWidget = new QListWidget(customJVMArgs_gb);
        customJVMArgs_listWidget->setObjectName(QString::fromUtf8("customJVMArgs_listWidget"));
        customJVMArgs_listWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
        customJVMArgs_listWidget->setDragEnabled(true);
        customJVMArgs_listWidget->setDragDropMode(QAbstractItemView::InternalMove);
        customJVMArgs_listWidget->setDefaultDropAction(Qt::MoveAction);
        customJVMArgs_listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout_7->addWidget(customJVMArgs_listWidget, 0, 1, 5, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_5, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_7, 0, 0, 1, 1);


        verticalLayout->addWidget(customJVMArgs_gb);

        line_2 = new QFrame(groupBox_5);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        groupBox = new QGroupBox(groupBox_5);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        minMem_label = new QLabel(groupBox);
        minMem_label->setObjectName(QString::fromUtf8("minMem_label"));

        horizontalLayout_2->addWidget(minMem_label);

        minMem_sb = new QSpinBox(groupBox);
        minMem_sb->setObjectName(QString::fromUtf8("minMem_sb"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(minMem_sb->sizePolicy().hasHeightForWidth());
        minMem_sb->setSizePolicy(sizePolicy);
        minMem_sb->setMaximum(999999999);

        horizontalLayout_2->addWidget(minMem_sb);


        verticalLayout_6->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        maxMem_label = new QLabel(groupBox);
        maxMem_label->setObjectName(QString::fromUtf8("maxMem_label"));

        horizontalLayout->addWidget(maxMem_label);

        maxMem_sb = new QSpinBox(groupBox);
        maxMem_sb->setObjectName(QString::fromUtf8("maxMem_sb"));
        sizePolicy.setHeightForWidth(maxMem_sb->sizePolicy().hasHeightForWidth());
        maxMem_sb->setSizePolicy(sizePolicy);
        maxMem_sb->setMaximum(999999999);

        horizontalLayout->addWidget(maxMem_sb);


        verticalLayout_6->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox);


        gridLayout->addWidget(groupBox_5, 0, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        javaPath_label->setBuddy(javaPath_le);
        minMem_label->setBuddy(minMem_sb);
        maxMem_label->setBuddy(maxMem_sb);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(javaPath_le, autoJava_pb);
        QWidget::setTabOrder(autoJava_pb, javaPath_showPb);
        QWidget::setTabOrder(javaPath_showPb, officialPolicy_rb);
        QWidget::setTabOrder(officialPolicy_rb, KaminecPolicy_rb);
        QWidget::setTabOrder(KaminecPolicy_rb, CustomPolicy_rb);
        QWidget::setTabOrder(CustomPolicy_rb, minMem_sb);
        QWidget::setTabOrder(minMem_sb, maxMem_sb);

        retranslateUi(JavaTab);

        QMetaObject::connectSlotsByName(JavaTab);
    } // setupUi

    void retranslateUi(QWidget *JavaTab)
    {
        groupBox_5->setTitle(QApplication::translate("JavaTab", "JVM settings", nullptr));
        javaPath_label->setText(QApplication::translate("JavaTab", "Java Path:", nullptr));
        autoJava_pb->setText(QApplication::translate("JavaTab", "Auto", nullptr));
        javaPath_showPb->setText(QApplication::translate("JavaTab", "Show...", nullptr));
        groupBox_7->setTitle(QApplication::translate("JavaTab", "Arguments Policy", nullptr));
        officialPolicy_rb->setText(QApplication::translate("JavaTab", "Offial", nullptr));
        KaminecPolicy_rb->setText(QApplication::translate("JavaTab", "Kaminec", nullptr));
        CustomPolicy_rb->setText(QApplication::translate("JavaTab", "Custom", nullptr));
        customJVMArgs_gb->setTitle(QApplication::translate("JavaTab", "Custom JVM Arguments", nullptr));
        removeArg_pushButton->setText(QApplication::translate("JavaTab", "Remove", nullptr));
        addArg_pushButton->setText(QApplication::translate("JavaTab", "Add", nullptr));
        groupBox->setTitle(QApplication::translate("JavaTab", "Memory Settings", nullptr));
        minMem_label->setText(QApplication::translate("JavaTab", "Minimum Memory Allocate:", nullptr));
        maxMem_label->setText(QApplication::translate("JavaTab", "Maximum Memory Allocate:", nullptr));
        Q_UNUSED(JavaTab);
    } // retranslateUi

};

namespace Ui {
    class JavaTab: public Ui_JavaTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JAVATAB_H
