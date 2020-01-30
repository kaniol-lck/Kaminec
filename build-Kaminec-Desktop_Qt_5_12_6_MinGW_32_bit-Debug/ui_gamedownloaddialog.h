/********************************************************************************
** Form generated from reading UI file 'gamedownloaddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEDOWNLOADDIALOG_H
#define UI_GAMEDOWNLOADDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GameDownloadDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *gameDownload_tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *download_pb;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;
    QCheckBox *hideUrl_checkBox;
    QCheckBox *hideReleaseTime_checkBox;
    QCheckBox *hideTime_checkBox;
    QFrame *line;
    QCheckBox *enableSnapshot_checkBox;
    QCheckBox *enableOldBeta_checkBox;
    QCheckBox *enableOldAlpha_checkBox;

    void setupUi(QDialog *GameDownloadDialog)
    {
        if (GameDownloadDialog->objectName().isEmpty())
            GameDownloadDialog->setObjectName(QString::fromUtf8("GameDownloadDialog"));
        GameDownloadDialog->resize(478, 394);
        horizontalLayout = new QHBoxLayout(GameDownloadDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gameDownload_tableView = new QTableView(GameDownloadDialog);
        gameDownload_tableView->setObjectName(QString::fromUtf8("gameDownload_tableView"));
        gameDownload_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        gameDownload_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        gameDownload_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        gameDownload_tableView->setSortingEnabled(true);
        gameDownload_tableView->horizontalHeader()->setDefaultSectionSize(21);
        gameDownload_tableView->horizontalHeader()->setHighlightSections(false);
        gameDownload_tableView->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(gameDownload_tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        download_pb = new QPushButton(GameDownloadDialog);
        download_pb->setObjectName(QString::fromUtf8("download_pb"));
        download_pb->setEnabled(false);

        verticalLayout->addWidget(download_pb);

        buttonBox = new QDialogButtonBox(GameDownloadDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        hideUrl_checkBox = new QCheckBox(GameDownloadDialog);
        hideUrl_checkBox->setObjectName(QString::fromUtf8("hideUrl_checkBox"));

        verticalLayout->addWidget(hideUrl_checkBox);

        hideReleaseTime_checkBox = new QCheckBox(GameDownloadDialog);
        hideReleaseTime_checkBox->setObjectName(QString::fromUtf8("hideReleaseTime_checkBox"));

        verticalLayout->addWidget(hideReleaseTime_checkBox);

        hideTime_checkBox = new QCheckBox(GameDownloadDialog);
        hideTime_checkBox->setObjectName(QString::fromUtf8("hideTime_checkBox"));

        verticalLayout->addWidget(hideTime_checkBox);

        line = new QFrame(GameDownloadDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        enableSnapshot_checkBox = new QCheckBox(GameDownloadDialog);
        enableSnapshot_checkBox->setObjectName(QString::fromUtf8("enableSnapshot_checkBox"));

        verticalLayout->addWidget(enableSnapshot_checkBox);

        enableOldBeta_checkBox = new QCheckBox(GameDownloadDialog);
        enableOldBeta_checkBox->setObjectName(QString::fromUtf8("enableOldBeta_checkBox"));

        verticalLayout->addWidget(enableOldBeta_checkBox);

        enableOldAlpha_checkBox = new QCheckBox(GameDownloadDialog);
        enableOldAlpha_checkBox->setObjectName(QString::fromUtf8("enableOldAlpha_checkBox"));

        verticalLayout->addWidget(enableOldAlpha_checkBox);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(GameDownloadDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GameDownloadDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GameDownloadDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GameDownloadDialog);
    } // setupUi

    void retranslateUi(QDialog *GameDownloadDialog)
    {
        GameDownloadDialog->setWindowTitle(QApplication::translate("GameDownloadDialog", "Game Download", nullptr));
        download_pb->setText(QApplication::translate("GameDownloadDialog", "Download", nullptr));
        hideUrl_checkBox->setText(QApplication::translate("GameDownloadDialog", "Hide Url", nullptr));
        hideReleaseTime_checkBox->setText(QApplication::translate("GameDownloadDialog", "Hide Release Time", nullptr));
        hideTime_checkBox->setText(QApplication::translate("GameDownloadDialog", "Hide Time", nullptr));
        enableSnapshot_checkBox->setText(QApplication::translate("GameDownloadDialog", "Enable Snapshot", nullptr));
        enableOldBeta_checkBox->setText(QApplication::translate("GameDownloadDialog", "Enable Old Beta", nullptr));
        enableOldAlpha_checkBox->setText(QApplication::translate("GameDownloadDialog", "Enable Old Alpha", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameDownloadDialog: public Ui_GameDownloadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEDOWNLOADDIALOG_H
