#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "downloadmanager.h"
#include "downloadmanagerplus.h"
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
#include <QProcess>
#include <QStandardItemModel>

KaminecLauncher::KaminecLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KaminecLauncher),
    SavesManager(this)
{
    ui->setupUi(this);

	ui->isOriginalName_cb->setChecked(true);
	ui->verifyBox->setVisible(false);
	ui->password_le->setEchoMode(QLineEdit::Password);

    ui->downloadProgress_label->setVisible(false);
    ui->downloadProgress_progressBar->setVisible(false);
    ui->downloadProgress_progressBar_2->setVisible(false);
    ui->downloadValue_label->setVisible(false);

	ui->saveMgr_treeView->setModel(SavesManager.getModel());
	if(!QFile("./version_manifest.json").exists()){
		auto dm = new DownloadManager(this);
		auto versions = FileItem(QString("version_manifest.json"),
								 0,
								 QString("NULL"),
								 QString("./version_manifest.json"),
								 QUrl("https://launchermeta.mojang.com/mc/game/version_manifest.json"));
		dm->append(versions);
		dm->waitForFinished();
	}

    //加载版本
    QFile jsonFile("./version_manifest.json");

    if(!jsonFile.exists())qDebug()<<"jsonfile file does not exist";
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Open failed";
        QMessageBox::about(0,"Not find json file","Json file NOT find,The program will terminate.");
    }
    qDebug()<<"versionfile.json file opened";

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
	return Profile{
				ui->username_le->text(),
				ui->version_cb->currentText(),
				QDir(ui->gameDir_le->text()).absolutePath(),
				QDir(ui->javaDir_le->text()).absolutePath(),

				ui->minMem_sb->value(),
				ui->maxMem_sb->value(),

				ui->width_sb->value(),
				ui->height_sb->value()
	};
}

QPair<QString, QString> KaminecLauncher::getAccount()
{
	return qMakePair(ui->email_le->text(),ui->password_le->text());
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
	auto dmp = new DownloadManagerPlus(this);

	ui->download_treeView->setModel(dmp->getModel());
    ui->download_pb->setText("Downloading...");
    ui->download_pb->setDisabled(true);
    ui->downloadProgress_label->setVisible(true);
    ui->downloadProgress_progressBar->setVisible(true);
    ui->downloadProgress_progressBar_2->setVisible(true);
    ui->downloadValue_label->setVisible(true);

	qDebug()<<"???"<<QString("%1/versions/%2/%2.json")
			  .arg(ui->gameDir_le->text()).arg(ui->version_cb->currentText());

    auto fileItem = FileItem(QString("%1.json").arg(ui->version_cb->currentText()),
                             0,
                             QString("NULL"),
							 QString("%1/versions/%2/%2.json")
								 .arg(ui->gameDir_le->text()).arg(ui->version_cb->currentText()),
                             versionList.at(ui->version_cb->currentIndex()).toMap().value("url").toUrl());
    dm->append(fileItem);
    dm->waitForFinished();

    JsonManager jm(this,ui->gameDir_le->text(),ui->version_cb->currentText());

    fileItem = FileItem(QString("%1.jar").arg(ui->version_cb->currentText()),
                        0,
                        QString("NULL"),
						QString("%1/versions/%2/%2.jar")
							.arg(ui->gameDir_le->text()).arg(ui->version_cb->currentText()),
                        jm.getDownloadClientUrl());
    qDebug()<<jm.getDownloadClientUrl();
	dmp->append(fileItem);


    auto downloadLibUrls = jm.getDownloadLibUrls();
    for(auto& i:downloadLibUrls){
        i.mPath.prepend(ui->gameDir_le->text()+"/libraries/");
        //qDebug()<<i.name;
    }

	dmp->append(downloadLibUrls);

    //qDebug()<<"before";
    auto downloadAssertUrls = jm.getDownloadAssertUrls();
    //qDebug()<<"after";
    for(auto& i:downloadAssertUrls){
        i.mPath.prepend(ui->gameDir_le->text()+"/assets/objects/");
        //qDebug()<<i.name;
    }
	dmp->append(downloadAssertUrls);

	qDebug()<<dmp->getTotalCount();

	totalCount = dmp->getTotalCount();
    ui->downloadValue_label->setText(QString("0/%1").arg(totalCount));
	ui->downloadProgress_progressBar->setMaximum(dmp->getTotalCount());
	ui->downloadProgress_progressBar_2->setMaximum(dmp->getTotalCount());

    //QStandardItemModel model;
    //ui->download_treeView->setModel(model);

	connect(dmp,SIGNAL(downloadedCountChanged(int)),this,SLOT(updateDownloadCount(int)));
	connect(dmp,SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar,SLOT(setValue(int)));
	connect(dmp,SIGNAL(downloadedCountChanged(int)),ui->downloadProgress_progressBar_2,SLOT(setValue(int)));
	connect(dmp,SIGNAL(finished()),this,SLOT(downloadFinished()));
	dmp->waitForFinished();
    return 0;
}

//选择游戏目录
void KaminecLauncher::on_fileDlg1_pb_clicked()
{
	auto gamePath = QFileDialog::getExistingDirectory(this,
													  "Choose game directory...");
	if(gamePath!="")
		ui->gameDir_le->setText(gamePath);
}

//选择javaw.exe路径
void KaminecLauncher::on_fileDlg2_pb_clicked()
{
	auto javaPath = QFileDialog::getOpenFileName(this,
												 "Choose javaw,exe...",
												 "C:/","javaw(javaw.exe)");
	if(javaPath!="")
		ui->javaDir_le->setText(javaPath);
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
	this->startGame();
}


void KaminecLauncher::on_download_pb_clicked()
{
    this->download();
}

void KaminecLauncher::updateDownloadCount(int downloaded)
{
    qDebug()<<"changed:"<<downloaded;
	ui->downloadValue_label->setText(QString("%1/%2")
									 .arg(downloaded).arg(totalCount));
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
//	ui->saveMgr_treeView->currentIndex()
}

void KaminecLauncher::on_backupSaves_pb_clicked()
{
    SavesManager.backup();
}

void KaminecLauncher::on_autoJavaPath_pb_clicked()
{
	auto environment = QProcess::systemEnvironment();
	auto PATH = environment.at(environment.indexOf(QRegExp("PATH=.*")))
						   .split(";");
	auto index = PATH.indexOf(QRegExp(".*\\javapath"));
	if(index==-1){
		QMessageBox::warning(this,
							 "Cannot find java path in environment...",
							 "Cannot find java path in environment,plaese choose it manually");
		return;
	}
	auto javaPath = PATH.at(index);
	javaPath.replace('\\',"/");
	ui->javaDir_le->setText(javaPath+"/javaw.exe");
//	qDebug()<<javaPath;

}

void KaminecLauncher::startGame()
{
	Game *game;
	if(ui->verify_cb->isChecked()){
		game = new Game(this,this->getProfile(),Mode::Online,
						this->getAccount(),ui->isOriginalName_cb->isChecked());
	}else{
		game = new Game(this,this->getProfile(),Mode::Offline,
						this->getAccount(),ui->isOriginalName_cb->isChecked());
	}
	ui->start_pb->setText("Gaming...");
	ui->start_pb->setDisabled(true);
	connect(game,SIGNAL(finished(int)),this,SLOT(gameFinished()));
	game->start();

}

void KaminecLauncher::on_showPassword_pb_clicked()
{
	if(isShowPassword){
		ui->password_le->setEchoMode(QLineEdit::Password);
		ui->showPassword_pb->setText("Show password");
		isShowPassword = !isShowPassword;
	}else{
		ui->password_le->setEchoMode(QLineEdit::Normal);
		ui->showPassword_pb->setText("Hide passeord");
		isShowPassword = !isShowPassword;
	}
}

void KaminecLauncher::on_verify_cb_stateChanged(int arg1)
{
	if(arg1){
		ui->verifyBox->setVisible(true);
	}else{
		ui->verifyBox->setVisible(false);
	}
}
