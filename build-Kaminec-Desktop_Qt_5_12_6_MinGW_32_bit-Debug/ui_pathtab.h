/********************************************************************************
** Form generated from reading UI file 'pathtab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATHTAB_H
#define UI_PATHTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PathTab
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_13;
    QCheckBox *defaultPath_checkBox;
    QPushButton *more_pb;
    QGridLayout *gridLayout_15;
    QLabel *javaPath_label_2;
    QLineEdit *javaPath_le_2;
    QPushButton *autoJava_pb_2;
    QPushButton *javaPath_showPb_2;
    QFrame *line_5;
    QGridLayout *gridLayout_12;
    QPushButton *indexesPath_showPb;
    QLineEdit *assetsPath_le;
    QLineEdit *corePath_le;
    QLabel *corePath_label;
    QPushButton *corePath_showPb;
    QLabel *versionsPath_label;
    QLabel *libsPath_label;
    QPushButton *libsPath_showPb;
    QLineEdit *versionsPath_le;
    QLineEdit *nativesPath_le;
    QLabel *assetsPath_label;
    QLabel *nativesPath_label;
    QPushButton *nativesPath_showPb;
    QLineEdit *libsPath_le;
    QPushButton *versionsPath_showPb;
    QLineEdit *indexesPath_le;
    QLabel *objectsPath_label;
    QLineEdit *objectsPath_le;
    QPushButton *objectsPath_showPb;
    QPushButton *assetsPath_showPb;
    QLabel *indexesPath_label;
    QPushButton *defaultGamePath_showPb;
    QLabel *defaultGamePath_label;
    QLineEdit *defaultGamePath_le;
    QFrame *line_4;
    QGridLayout *gridLayout_2;
    QLabel *unusedModsPath_label;
    QLabel *loggerPath_label;
    QLabel *savesBackupPath_label;
    QLineEdit *loggerPath_le;
    QLineEdit *unusedModsPath_le;
    QPushButton *unusedModsPath_showPb;
    QPushButton *savesBackupPath_showPb;
    QLineEdit *savesBackupPath_le;
    QPushButton *loggerPath_showPb;
    QTextBrowser *customPathHelper_tb;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PathTab)
    {
        if (PathTab->objectName().isEmpty())
            PathTab->setObjectName(QString::fromUtf8("PathTab"));
        PathTab->resize(400, 600);
        PathTab->setWindowTitle(QString::fromUtf8("Form"));
        gridLayout = new QGridLayout(PathTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_2 = new QGroupBox(PathTab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        defaultPath_checkBox = new QCheckBox(groupBox_2);
        defaultPath_checkBox->setObjectName(QString::fromUtf8("defaultPath_checkBox"));

        gridLayout_13->addWidget(defaultPath_checkBox, 0, 0, 1, 1);

        more_pb = new QPushButton(groupBox_2);
        more_pb->setObjectName(QString::fromUtf8("more_pb"));
        more_pb->setCheckable(true);

        gridLayout_13->addWidget(more_pb, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_13);

        gridLayout_15 = new QGridLayout();
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        javaPath_label_2 = new QLabel(groupBox_2);
        javaPath_label_2->setObjectName(QString::fromUtf8("javaPath_label_2"));

        gridLayout_15->addWidget(javaPath_label_2, 0, 0, 1, 1);

        javaPath_le_2 = new QLineEdit(groupBox_2);
        javaPath_le_2->setObjectName(QString::fromUtf8("javaPath_le_2"));

        gridLayout_15->addWidget(javaPath_le_2, 0, 1, 1, 1);

        autoJava_pb_2 = new QPushButton(groupBox_2);
        autoJava_pb_2->setObjectName(QString::fromUtf8("autoJava_pb_2"));

        gridLayout_15->addWidget(autoJava_pb_2, 0, 2, 1, 1);

        javaPath_showPb_2 = new QPushButton(groupBox_2);
        javaPath_showPb_2->setObjectName(QString::fromUtf8("javaPath_showPb_2"));

        gridLayout_15->addWidget(javaPath_showPb_2, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_15);

        line_5 = new QFrame(groupBox_2);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_5);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        indexesPath_showPb = new QPushButton(groupBox_2);
        indexesPath_showPb->setObjectName(QString::fromUtf8("indexesPath_showPb"));
        indexesPath_showPb->setEnabled(true);

        gridLayout_12->addWidget(indexesPath_showPb, 8, 2, 1, 1);

        assetsPath_le = new QLineEdit(groupBox_2);
        assetsPath_le->setObjectName(QString::fromUtf8("assetsPath_le"));
        assetsPath_le->setEnabled(true);

        gridLayout_12->addWidget(assetsPath_le, 7, 1, 1, 1);

        corePath_le = new QLineEdit(groupBox_2);
        corePath_le->setObjectName(QString::fromUtf8("corePath_le"));
        corePath_le->setEnabled(true);

        gridLayout_12->addWidget(corePath_le, 0, 1, 1, 1);

        corePath_label = new QLabel(groupBox_2);
        corePath_label->setObjectName(QString::fromUtf8("corePath_label"));
        corePath_label->setEnabled(true);

        gridLayout_12->addWidget(corePath_label, 0, 0, 1, 1);

        corePath_showPb = new QPushButton(groupBox_2);
        corePath_showPb->setObjectName(QString::fromUtf8("corePath_showPb"));
        corePath_showPb->setEnabled(true);

        gridLayout_12->addWidget(corePath_showPb, 0, 2, 1, 1);

        versionsPath_label = new QLabel(groupBox_2);
        versionsPath_label->setObjectName(QString::fromUtf8("versionsPath_label"));
        versionsPath_label->setEnabled(true);

        gridLayout_12->addWidget(versionsPath_label, 4, 0, 1, 1);

        libsPath_label = new QLabel(groupBox_2);
        libsPath_label->setObjectName(QString::fromUtf8("libsPath_label"));
        libsPath_label->setEnabled(true);

        gridLayout_12->addWidget(libsPath_label, 5, 0, 1, 1);

        libsPath_showPb = new QPushButton(groupBox_2);
        libsPath_showPb->setObjectName(QString::fromUtf8("libsPath_showPb"));
        libsPath_showPb->setEnabled(true);

        gridLayout_12->addWidget(libsPath_showPb, 5, 2, 1, 1);

        versionsPath_le = new QLineEdit(groupBox_2);
        versionsPath_le->setObjectName(QString::fromUtf8("versionsPath_le"));
        versionsPath_le->setEnabled(true);

        gridLayout_12->addWidget(versionsPath_le, 4, 1, 1, 1);

        nativesPath_le = new QLineEdit(groupBox_2);
        nativesPath_le->setObjectName(QString::fromUtf8("nativesPath_le"));
        nativesPath_le->setEnabled(true);

        gridLayout_12->addWidget(nativesPath_le, 6, 1, 1, 1);

        assetsPath_label = new QLabel(groupBox_2);
        assetsPath_label->setObjectName(QString::fromUtf8("assetsPath_label"));
        assetsPath_label->setEnabled(true);

        gridLayout_12->addWidget(assetsPath_label, 7, 0, 1, 1);

        nativesPath_label = new QLabel(groupBox_2);
        nativesPath_label->setObjectName(QString::fromUtf8("nativesPath_label"));
        nativesPath_label->setEnabled(true);

        gridLayout_12->addWidget(nativesPath_label, 6, 0, 1, 1);

        nativesPath_showPb = new QPushButton(groupBox_2);
        nativesPath_showPb->setObjectName(QString::fromUtf8("nativesPath_showPb"));
        nativesPath_showPb->setEnabled(true);

        gridLayout_12->addWidget(nativesPath_showPb, 6, 2, 1, 1);

        libsPath_le = new QLineEdit(groupBox_2);
        libsPath_le->setObjectName(QString::fromUtf8("libsPath_le"));
        libsPath_le->setEnabled(true);

        gridLayout_12->addWidget(libsPath_le, 5, 1, 1, 1);

        versionsPath_showPb = new QPushButton(groupBox_2);
        versionsPath_showPb->setObjectName(QString::fromUtf8("versionsPath_showPb"));
        versionsPath_showPb->setEnabled(true);

        gridLayout_12->addWidget(versionsPath_showPb, 4, 2, 1, 1);

        indexesPath_le = new QLineEdit(groupBox_2);
        indexesPath_le->setObjectName(QString::fromUtf8("indexesPath_le"));
        indexesPath_le->setEnabled(true);

        gridLayout_12->addWidget(indexesPath_le, 8, 1, 1, 1);

        objectsPath_label = new QLabel(groupBox_2);
        objectsPath_label->setObjectName(QString::fromUtf8("objectsPath_label"));
        objectsPath_label->setEnabled(true);

        gridLayout_12->addWidget(objectsPath_label, 9, 0, 1, 1);

        objectsPath_le = new QLineEdit(groupBox_2);
        objectsPath_le->setObjectName(QString::fromUtf8("objectsPath_le"));
        objectsPath_le->setEnabled(true);

        gridLayout_12->addWidget(objectsPath_le, 9, 1, 1, 1);

        objectsPath_showPb = new QPushButton(groupBox_2);
        objectsPath_showPb->setObjectName(QString::fromUtf8("objectsPath_showPb"));
        objectsPath_showPb->setEnabled(true);

        gridLayout_12->addWidget(objectsPath_showPb, 9, 2, 1, 1);

        assetsPath_showPb = new QPushButton(groupBox_2);
        assetsPath_showPb->setObjectName(QString::fromUtf8("assetsPath_showPb"));
        assetsPath_showPb->setEnabled(true);

        gridLayout_12->addWidget(assetsPath_showPb, 7, 2, 1, 1);

        indexesPath_label = new QLabel(groupBox_2);
        indexesPath_label->setObjectName(QString::fromUtf8("indexesPath_label"));
        indexesPath_label->setEnabled(true);

        gridLayout_12->addWidget(indexesPath_label, 8, 0, 1, 1);

        defaultGamePath_showPb = new QPushButton(groupBox_2);
        defaultGamePath_showPb->setObjectName(QString::fromUtf8("defaultGamePath_showPb"));
        defaultGamePath_showPb->setEnabled(true);

        gridLayout_12->addWidget(defaultGamePath_showPb, 1, 2, 3, 1);

        defaultGamePath_label = new QLabel(groupBox_2);
        defaultGamePath_label->setObjectName(QString::fromUtf8("defaultGamePath_label"));
        defaultGamePath_label->setEnabled(true);

        gridLayout_12->addWidget(defaultGamePath_label, 1, 0, 3, 1);

        defaultGamePath_le = new QLineEdit(groupBox_2);
        defaultGamePath_le->setObjectName(QString::fromUtf8("defaultGamePath_le"));
        defaultGamePath_le->setEnabled(true);

        gridLayout_12->addWidget(defaultGamePath_le, 1, 1, 3, 1);


        verticalLayout->addLayout(gridLayout_12);

        line_4 = new QFrame(groupBox_2);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        unusedModsPath_label = new QLabel(groupBox_2);
        unusedModsPath_label->setObjectName(QString::fromUtf8("unusedModsPath_label"));
        unusedModsPath_label->setEnabled(true);

        gridLayout_2->addWidget(unusedModsPath_label, 0, 0, 1, 1);

        loggerPath_label = new QLabel(groupBox_2);
        loggerPath_label->setObjectName(QString::fromUtf8("loggerPath_label"));
        loggerPath_label->setEnabled(true);

        gridLayout_2->addWidget(loggerPath_label, 2, 0, 1, 1);

        savesBackupPath_label = new QLabel(groupBox_2);
        savesBackupPath_label->setObjectName(QString::fromUtf8("savesBackupPath_label"));
        savesBackupPath_label->setEnabled(true);

        gridLayout_2->addWidget(savesBackupPath_label, 1, 0, 1, 1);

        loggerPath_le = new QLineEdit(groupBox_2);
        loggerPath_le->setObjectName(QString::fromUtf8("loggerPath_le"));
        loggerPath_le->setEnabled(true);

        gridLayout_2->addWidget(loggerPath_le, 2, 1, 1, 1);

        unusedModsPath_le = new QLineEdit(groupBox_2);
        unusedModsPath_le->setObjectName(QString::fromUtf8("unusedModsPath_le"));
        unusedModsPath_le->setEnabled(true);

        gridLayout_2->addWidget(unusedModsPath_le, 0, 1, 1, 1);

        unusedModsPath_showPb = new QPushButton(groupBox_2);
        unusedModsPath_showPb->setObjectName(QString::fromUtf8("unusedModsPath_showPb"));
        unusedModsPath_showPb->setEnabled(true);

        gridLayout_2->addWidget(unusedModsPath_showPb, 0, 2, 1, 1);

        savesBackupPath_showPb = new QPushButton(groupBox_2);
        savesBackupPath_showPb->setObjectName(QString::fromUtf8("savesBackupPath_showPb"));
        savesBackupPath_showPb->setEnabled(true);

        gridLayout_2->addWidget(savesBackupPath_showPb, 1, 2, 1, 1);

        savesBackupPath_le = new QLineEdit(groupBox_2);
        savesBackupPath_le->setObjectName(QString::fromUtf8("savesBackupPath_le"));
        savesBackupPath_le->setEnabled(true);

        gridLayout_2->addWidget(savesBackupPath_le, 1, 1, 1, 1);

        loggerPath_showPb = new QPushButton(groupBox_2);
        loggerPath_showPb->setObjectName(QString::fromUtf8("loggerPath_showPb"));
        loggerPath_showPb->setEnabled(true);

        gridLayout_2->addWidget(loggerPath_showPb, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        customPathHelper_tb = new QTextBrowser(groupBox_2);
        customPathHelper_tb->setObjectName(QString::fromUtf8("customPathHelper_tb"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(customPathHelper_tb->sizePolicy().hasHeightForWidth());
        customPathHelper_tb->setSizePolicy(sizePolicy);
        customPathHelper_tb->setMinimumSize(QSize(0, 60));
        customPathHelper_tb->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);"));

        verticalLayout->addWidget(customPathHelper_tb);

        verticalSpacer = new QSpacerItem(17, 68, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        javaPath_label_2->setBuddy(javaPath_le_2);
        corePath_label->setBuddy(corePath_le);
        versionsPath_label->setBuddy(versionsPath_le);
        libsPath_label->setBuddy(libsPath_le);
        assetsPath_label->setBuddy(assetsPath_le);
        nativesPath_label->setBuddy(nativesPath_le);
        objectsPath_label->setBuddy(objectsPath_le);
        indexesPath_label->setBuddy(indexesPath_le);
        defaultGamePath_label->setBuddy(corePath_le);
        unusedModsPath_label->setBuddy(unusedModsPath_le);
        loggerPath_label->setBuddy(loggerPath_le);
        savesBackupPath_label->setBuddy(savesBackupPath_le);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(defaultPath_checkBox, more_pb);
        QWidget::setTabOrder(more_pb, javaPath_le_2);
        QWidget::setTabOrder(javaPath_le_2, autoJava_pb_2);
        QWidget::setTabOrder(autoJava_pb_2, javaPath_showPb_2);
        QWidget::setTabOrder(javaPath_showPb_2, corePath_le);
        QWidget::setTabOrder(corePath_le, corePath_showPb);
        QWidget::setTabOrder(corePath_showPb, defaultGamePath_le);
        QWidget::setTabOrder(defaultGamePath_le, defaultGamePath_showPb);
        QWidget::setTabOrder(defaultGamePath_showPb, versionsPath_le);
        QWidget::setTabOrder(versionsPath_le, versionsPath_showPb);
        QWidget::setTabOrder(versionsPath_showPb, libsPath_le);
        QWidget::setTabOrder(libsPath_le, libsPath_showPb);
        QWidget::setTabOrder(libsPath_showPb, nativesPath_le);
        QWidget::setTabOrder(nativesPath_le, nativesPath_showPb);
        QWidget::setTabOrder(nativesPath_showPb, assetsPath_le);
        QWidget::setTabOrder(assetsPath_le, assetsPath_showPb);
        QWidget::setTabOrder(assetsPath_showPb, indexesPath_le);
        QWidget::setTabOrder(indexesPath_le, indexesPath_showPb);
        QWidget::setTabOrder(indexesPath_showPb, objectsPath_le);
        QWidget::setTabOrder(objectsPath_le, objectsPath_showPb);
        QWidget::setTabOrder(objectsPath_showPb, unusedModsPath_le);
        QWidget::setTabOrder(unusedModsPath_le, unusedModsPath_showPb);
        QWidget::setTabOrder(unusedModsPath_showPb, savesBackupPath_le);
        QWidget::setTabOrder(savesBackupPath_le, savesBackupPath_showPb);
        QWidget::setTabOrder(savesBackupPath_showPb, loggerPath_le);
        QWidget::setTabOrder(loggerPath_le, loggerPath_showPb);
        QWidget::setTabOrder(loggerPath_showPb, customPathHelper_tb);

        retranslateUi(PathTab);

        QMetaObject::connectSlotsByName(PathTab);
    } // setupUi

    void retranslateUi(QWidget *PathTab)
    {
        groupBox_2->setTitle(QApplication::translate("PathTab", "Path Settings", nullptr));
        defaultPath_checkBox->setText(QApplication::translate("PathTab", "Use Default Relative Path", nullptr));
        more_pb->setText(QApplication::translate("PathTab", "More", nullptr));
        javaPath_label_2->setText(QApplication::translate("PathTab", "Java Path:", nullptr));
        autoJava_pb_2->setText(QApplication::translate("PathTab", "Auto", nullptr));
        javaPath_showPb_2->setText(QApplication::translate("PathTab", "Show...", nullptr));
        indexesPath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        corePath_label->setText(QApplication::translate("PathTab", "Core Path:", nullptr));
        corePath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        versionsPath_label->setText(QApplication::translate("PathTab", "Version Folder Path:", nullptr));
        libsPath_label->setText(QApplication::translate("PathTab", "Libraries Path:", nullptr));
        libsPath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        assetsPath_label->setText(QApplication::translate("PathTab", "Assets Path:", nullptr));
        nativesPath_label->setText(QApplication::translate("PathTab", "Natives Extract Path:", nullptr));
        nativesPath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        versionsPath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        objectsPath_label->setText(QApplication::translate("PathTab", "Asset Objects Path:", nullptr));
        objectsPath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        assetsPath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        indexesPath_label->setText(QApplication::translate("PathTab", "Asset Indexes Path:", nullptr));
        defaultGamePath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        defaultGamePath_label->setText(QApplication::translate("PathTab", "Default Game Path:", nullptr));
        unusedModsPath_label->setText(QApplication::translate("PathTab", "Unused Mods Path:", nullptr));
        loggerPath_label->setText(QApplication::translate("PathTab", "Logger Path:", nullptr));
        savesBackupPath_label->setText(QApplication::translate("PathTab", "Saves Backup Path:", nullptr));
        unusedModsPath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        savesBackupPath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        loggerPath_showPb->setText(QApplication::translate("PathTab", "Show...", nullptr));
        customPathHelper_tb->setHtml(QApplication::translate("PathTab", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Core Path:&lt;core&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Assets Path:&lt;assets&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Launcher Path:&lt;launcher&gt;</span></p></body></html>", nullptr));
        Q_UNUSED(PathTab);
    } // retranslateUi

};

namespace Ui {
    class PathTab: public Ui_PathTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATHTAB_H
