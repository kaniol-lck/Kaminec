#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "downloadmanager.h"
#include "JsonManager.h"
#include "gamemode.h"
#include "game.h"
#include "fileitem.h"

#include <algorithm>
#include <QTime>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>
#include <QStandardItemModel>

KaminecLauncher::KaminecLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KaminecLauncher),
    SavesManager(this)
{
    ui->setupUi(this);
    ui->downloadProgress_label->setVisible(false);
    ui->downloadProgress_progressBar->setVisible(false);
    ui->downloadProgress_progressBar_2->setVisible(false);
    ui->downloadValue_label->setVisible(false);

    ui->saveMgr_treeView->setModel(SavesManager.getModel());
    auto dm = new DownloadManager(this);
    auto versions = FileItem(QString("version_manifest.json"),
                             26389,
                             QString("NULL"),
                             QString("./version_manifest.json"),
                             QUrl("https://launchermeta.mojang.com/mc/game/version_manifest.json"));
    if(dm->append(versions)==0){
        dm->waitForFinished();
    }
    //加载版本
    QFile jsonFile("./version_manifest.json");

    if(!jsonFile.exists())qDebug()<<"jsonfile file does not exist";
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Open failed";
        QMessageBox::about(0,"Not find json file","Json file NOT find,The program will terminate.");
    }
    qDebug()<<"versionfile.json) file opened";

    QByteArray jsonByte;
    jsonByte.resize(jsonFile.bytesAvailable());
    jsonByte = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError ok;
    auto jsonDoc = QJsonDocument::fromJson(jsonByte,&ok);
    if(ok.error != QJsonParseError::NoError){qDebug()<<"Json failed."<<endl<<ok.error;}

    auto jsonMap = jsonDoc.toVariant().toMap();
    versionList = jsonMap.value("versions").toList();
    ui->version_cb->addItems(std::accumulate(versionList.begin(),versionList.end(),QStringList(),
                                             [](QStringList versionNameList,QVariant versionElem){
                                 return versionNameList<<versionElem
                                        .toMap().value("id").toString();
                             }));

    this->loadProfileJson();
}

KaminecLauncher::~KaminecLauncher()
{
    delete ui;
}

//获取当前选择的profile
inline const Profile KaminecLauncher::getProfile()
{
    return Profile{ui->username_le->text(),
                   ui->version_cb->currentText(),
                   QDir(ui->gameDir_le->text()).absolutePath(),
                   QDir(ui->javaDir_le->text()).absolutePath(),

                   ui->minMem_sb->value(),
                   ui->maxMem_sb->value(),

                   ui->width_sb->value(),
                   ui->height_sb->value()};
}

void KaminecLauncher::loadProfileJson()
{
    QFile loadfile("profile.json");
    if(!loadfile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(this,"File not exist.",R"(It's no file called "profile.json".)");
        return;
    }


    QByteArray bytes = loadfile.readAll();
    loadfile.close();

    //解析json
    QJsonParseError ok;
    QJsonDocument loadDoc = QJsonDocument::fromJson(bytes,&ok);
    if(ok.error != QJsonParseError::NoError){
        QMessageBox::warning(this,"Calculate Failed",R"("profile.json" may be crashed.)");
        return;
    }

    QJsonObject loadProfile = loadDoc.object();

    //解析profile的json模型

    ui->username_le->setText(loadProfile.value("username").toString());
    ui->version_cb->setCurrentText(loadProfile.value("version").toString());
    ui->gameDir_le->setText(loadProfile.value("gameDir").toString());
    ui->javaDir_le->setText(loadProfile.value("javaDir").toString());

    ui->minMem_sb->setValue(loadProfile.value("minMem").toInt());
    ui->maxMem_sb->setValue(loadProfile.value("maxMem").toInt());

    ui->width_sb->setValue(loadProfile.value("width").toInt());
    ui->height_sb->setValue(loadProfile.value("height").toInt());
}

void KaminecLauncher::saveProfileJson()
{
    QJsonObject saveProfile;

    //生成profile的json模型

    saveProfile.insert("username",ui->username_le->text());
    saveProfile.insert("version",ui->version_cb->currentText());
    saveProfile.insert("gameDir",ui->gameDir_le->text());
    saveProfile.insert("javaDir",ui->javaDir_le->text());

    saveProfile.insert("minMem",ui->minMem_sb->value());
    saveProfile.insert("maxMem",ui->maxMem_sb->value());

    saveProfile.insert("width",ui->width_sb->value());
    saveProfile.insert("height",ui->height_sb->value());


    QJsonDocument saveDoc;
    saveDoc.setObject(saveProfile);

    QByteArray bytes = saveDoc.toJson(QJsonDocument::Compact);

    qDebug()<<bytes;

    //生成profile的json文档
    QFile savefile("profile.json");
    savefile.open(QIODevice::WriteOnly|QIODevice::Text);

    QTextStream output(&savefile);
    output<<bytes;
    savefile.close();
}

int KaminecLauncher::download()
{
    auto dm = new DownloadManager(this);

    ui->download_treeView->setModel(dm->getModel());
    ui->download_pb->setText("Downloading...");
    ui->download_pb->setDisabled(true);
    ui->downloadProgress_label->setVisible(true);
    ui->downloadProgress_progressBar->setVisible(true);
    ui->downloadProgress_progressBar_2->setVisible(true);
    ui->downloadValue_label->setVisible(true);

    qDebug()<<"???"<<QString("%1/versions/%2/%2.json").arg(ui->gameDir_le->text()).arg(ui->version_cb->currentText());
    auto fileItem = FileItem(QString("%1.json").arg(ui->version_cb->currentText()),
                             0,
                             QString("NULL"),
                             QString("%1/versions/%2/%2.json").arg(ui->gameDir_le->text()).arg(ui->version_cb->currentText()),
                             versionList.at(ui->version_cb->currentIndex()).toMap().value("url").toUrl());
    if(dm->append(fileItem)==1){
        dm->waitForFinished();
    }

    JsonManager jm(this,ui->gameDir_le->text(),ui->version_cb->currentText());

    fileItem = FileItem(QString("%1.jar").arg(ui->version_cb->currentText()),
                        0,
                        QString("NULL"),
                        QString("%1/versions/%2/%2.jar").arg(ui->gameDir_le->text()).arg(ui->version_cb->currentText()),
                        jm.getDownloadClientUrl());
    qDebug()<<jm.getDownloadClientUrl();
    if(dm->append(fileItem)==1){
        dm->waitForFinished();
    }

    auto downloadLibUrls = jm.getDownloadLibUrls();
    for(auto& i:downloadLibUrls){
        i.path.prepend(ui->gameDir_le->text()+"/libraries/");
        //qDebug()<<i.name;
    }

    if(dm->append(downloadLibUrls)==1){
        dm->waitForFinished();
    }
    //qDebug()<<"before";
    auto downloadAssertUrls = jm.getDownloadAssertUrls();
    //qDebug()<<"after";
    for(auto& i:downloadAssertUrls){
        i.path.prepend(ui->gameDir_le->text()+"/assets/objects/");
        //qDebug()<<i.name;
    }
    if(dm->append(downloadAssertUrls)==1){
        dm->waitForFinished();
    }

    qDebug()<<dm->getTotalCount();

    totalCount = dm->getTotalCount();
    ui->downloadValue_label->setText(QString("0/%1").arg(totalCount));
    ui->downloadProgress_progressBar->setMaximum(dm->getTotalCount());
    ui->downloadProgress_progressBar_2->setMaximum(dm->getTotalCount());

    //QStandardItemModel model;
    //ui->download_treeView->setModel(model);

    connect(dm,SIGNAL(downloadedCountChanged(int)),this,SLOT(updateDownloadCount(int)));
    connect(dm,SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar,SLOT(setValue(int)));
    connect(dm,SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar_2,SLOT(setValue(int)));
    connect(dm,SIGNAL(finished()),this,SLOT(downloadFinished()));
    if(dm->waitForFinished()==-1)return -1;
    return 0;
}

//选择游戏目录
void KaminecLauncher::on_fileDlg1_pb_clicked()
{
    ui->gameDir_le->setText(
                QFileDialog::getExistingDirectory(this,"Choose game directory..."));
}

//选择javaw.exe路径
void KaminecLauncher::on_fileDlg2_pb_clicked()
{
    ui->javaDir_le->setText(
                QFileDialog::getOpenFileName(this,"Choose javaw,exe...","C:/","javaw(javaw.exe)"));
}

//保存profile文件
void KaminecLauncher::on_save_pb_clicked()
{
    this->saveProfileJson();
}

//载入profile文件
void KaminecLauncher::on_load_pb_clicked()
{
    this->loadProfileJson();
}


void KaminecLauncher::on_start_pb_clicked()
{
    auto g=new Game(this,this->getProfile(),Mode::Online);
    g->start();
    ui->start_pb->setText("Gaming...");
    ui->start_pb->setDisabled(true);
    connect(g,SIGNAL(finished(int)),this,SLOT(gameFinished()));

}

void KaminecLauncher::on_pushButton_clicked()
{
    Game g(this,this->getProfile(),Mode::Online);
    QTime t;
    g.genStartcode();
    auto time = t.elapsed();
    QFile ttf("timeTest.txt");
    ttf.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Append);

    QTextStream out2(&ttf);
    out2<<time<<endl;
}

void KaminecLauncher::on_pushButton_2_clicked()
{
    QFile ttf("timeTest.txt");
    ttf.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Append);
    QTextStream out2(&ttf);

    QTime at;
    Game g(this,this->getProfile(),Mode::Online);
    for(auto i=1;i!=10;++i){
        QTime t;
        g.genStartcode();
        auto time = t.elapsed();
        out2<<time<<endl;
    }

    out2<<"#10#"<<at.elapsed()<<endl;
}

void KaminecLauncher::on_pushButton_3_clicked()
{
    QFile ttf("timeTest.txt");
    ttf.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Append);
    QTextStream out2(&ttf);

    QTime at;
    Game g(this,this->getProfile(),Mode::Online);
    for(auto i=1;i!=100;++i){
        QTime t;
        g.genStartcode();
        auto time = t.elapsed();
        out2<<time<<endl;
    }

    out2<<"#100#"<<at.elapsed()<<endl;
}


void KaminecLauncher::on_download_pb_clicked()
{
    this->download();
}

void KaminecLauncher::updateDownloadCount(int downloaded)
{
    qDebug()<<"changed:"<<downloaded;
    ui->downloadValue_label->setText(QString("%1/%2").arg(downloaded).arg(totalCount));
}

void KaminecLauncher::downloadFinished()
{
    ui->download_pb->setText("&Download");
    ui->download_pb->setEnabled(true);
    ui->downloadProgress_label->setVisible(false);
    ui->downloadProgress_progressBar->setVisible(false);
    ui->downloadProgress_progressBar_2->setVisible(false);
    ui->downloadValue_label->setVisible(false);
}

void KaminecLauncher::gameFinished()
{
    qDebug()<<"finished";
    ui->start_pb->setText("&Start");
    ui->start_pb->setEnabled(true);
}

void KaminecLauncher::on_addSaves_pb_clicked()
{
    SavesManager.addSaves();
}

void KaminecLauncher::on_deleteSaves_pb_clicked()
{

}

void KaminecLauncher::on_backupSaves_pb_clicked()
{
    SavesManager.backup();
}
