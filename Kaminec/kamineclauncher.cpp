#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "downloadmanager.h"
#include "jsonmanager.h"
#include "gamemode.h"
#include "game.h"

#include <QTime>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>

KaminecLauncher::KaminecLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KaminecLauncher)
{
    ui->setupUi(this);
    this->loadProfileJson();
}

KaminecLauncher::~KaminecLauncher()
{
    delete ui;
}

//获取当前选择的profile
inline const profile KaminecLauncher::getProfile()
{
    return profile{ui->username_le->text(),
                   ui->version_le->text(),
                   ui->gameDir_le->text(),
                   ui->javaDir_le->text(),

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
    ui->version_le->setText(loadProfile.value("version").toString());
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
    saveProfile.insert("version",ui->version_le->text());
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
    jsonManager jm(ui->gameDir_le->text(),ui->version_le->text());
    downloadManager dm;
    auto downloadLibUrls = jm.getDownloadLibUrls();
    for(auto& i:downloadLibUrls){
        i.second.prepend(ui->gameDir_le->text()+"/libraries/");
        qDebug()<<i;
    }
    dm.append(downloadLibUrls);

    auto downloadAssertUrls = jm.getDownloadAssertUrls();
    for(auto& i:downloadAssertUrls){
        i.second.prepend(ui->gameDir_le->text()+"/assets/objects/");
        qDebug()<<i;
    }
    dm.append(downloadAssertUrls);

    if(dm.waitForFinished()==-1)return -1;
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
    game g(this->getProfile(),mode::Online);
    g.start();
}

void KaminecLauncher::on_pushButton_clicked()
{
    game g(this->getProfile(),mode::Online);
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
    game g(this->getProfile(),mode::Online);
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
    game g(this->getProfile(),mode::Online);
    for(auto i=1;i!=100;++i){
        QTime t;
        g.genStartcode();
        auto time = t.elapsed();
        out2<<time<<endl;
    }

    out2<<"#100#"<<at.elapsed()<<endl;
}


void KaminecLauncher::on_pushButton_4_clicked()
{
    qDebug()<<"Downloading";
}

void KaminecLauncher::on_download_pb_clicked()
{
    this->download();
}
