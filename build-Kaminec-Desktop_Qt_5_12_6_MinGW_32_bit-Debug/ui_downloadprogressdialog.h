/********************************************************************************
** Form generated from reading UI file 'downloadprogressdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADPROGRESSDIALOG_H
#define UI_DOWNLOADPROGRESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DownloadProgressDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QTreeView *download_treeView;
    QHBoxLayout *horizontalLayout;
    QProgressBar *downloadProgress_progressBar_2;
    QLabel *downloadValue_label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DownloadProgressDialog)
    {
        if (DownloadProgressDialog->objectName().isEmpty())
            DownloadProgressDialog->setObjectName(QString::fromUtf8("DownloadProgressDialog"));
        DownloadProgressDialog->resize(800, 540);
        horizontalLayout_2 = new QHBoxLayout(DownloadProgressDialog);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        download_treeView = new QTreeView(DownloadProgressDialog);
        download_treeView->setObjectName(QString::fromUtf8("download_treeView"));
        download_treeView->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);"));

        verticalLayout->addWidget(download_treeView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        downloadProgress_progressBar_2 = new QProgressBar(DownloadProgressDialog);
        downloadProgress_progressBar_2->setObjectName(QString::fromUtf8("downloadProgress_progressBar_2"));
        downloadProgress_progressBar_2->setSizeIncrement(QSize(0, 6));
        downloadProgress_progressBar_2->setValue(0);

        horizontalLayout->addWidget(downloadProgress_progressBar_2);

        downloadValue_label = new QLabel(DownloadProgressDialog);
        downloadValue_label->setObjectName(QString::fromUtf8("downloadValue_label"));
#ifndef QT_NO_WHATSTHIS
        downloadValue_label->setWhatsThis(QString::fromUtf8(""));
#endif // QT_NO_WHATSTHIS

        horizontalLayout->addWidget(downloadValue_label);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(DownloadProgressDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        retranslateUi(DownloadProgressDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DownloadProgressDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DownloadProgressDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DownloadProgressDialog);
    } // setupUi

    void retranslateUi(QDialog *DownloadProgressDialog)
    {
        DownloadProgressDialog->setWindowTitle(QApplication::translate("DownloadProgressDialog", "Download Progress", nullptr));
        downloadValue_label->setText(QApplication::translate("DownloadProgressDialog", "0/0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DownloadProgressDialog: public Ui_DownloadProgressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADPROGRESSDIALOG_H
