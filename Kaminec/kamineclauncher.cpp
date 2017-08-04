#include "kamineclauncher.h"
#include "ui_kamineclauncher.h"

#include "preference.h"
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
#include <QSettings>
#include <QStandardPaths>
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
	savesManager(this),
	corePath(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).toString())
{
	ui->setupUi(this);

    ui->downloadProgress_label->setVisible(false);
    ui->downloadProgress_progressBar->setVisible(false);
    ui->downloadProgress_progressBar_2->setVisible(false);
    ui->downloadValue_label->setVisible(false);

	ui->saveMgr_treeView->setModel(savesManager.getModel());
	if(!QFile("./version_manifest.json").exists()||
	   QFile("./version_manifest.json").size()==0){
		auto dm = new DownloadManager(this);
		auto versions = FileItem(QString("version_manifest.json"),
								 0,
								 QString("NULL"),
								 QString("./version_manifest.json"),
								 QUrl("https://launchermeta.mojang.com/mc/game/version_manifest.json"));
		dm->append(versions);
		dm->waitForFinished();
	}

	qDebug()<<"???";
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
											 [this](QStringList versionNameList,QVariant versionElem){
								 return versionNameList<<(versionElem
								 .toMap().value("id").toString() +
								 (QFile(QString("%1/versions/%2/%2.jar")
								 .arg(ui->gameDir_le->text())
								 .arg(versionElem.toMap().value("id").toString()))
								 .exists()?"(Downloaded)":""));
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
	return Profile::fromJson().value(ui->profileSelect_cb->currentText());//!!!!!!!
}

void KaminecLauncher::loadProfileJson()
{
	auto profiles = Profile::fromJson();
	for(auto profile:profiles){
		ui->profileSelect_cb->addItem(profile.mName);
	}

	auto selectedProfile = profiles.value(Profile::getSelectedProfile());
	ui->profileSelect_cb->setCurrentText(selectedProfile.mName);
	if(ui->version_cb->findText(selectedProfile.mLastVersionId)==-1){
		ui->version_cb->addItem(selectedProfile.mLastVersionId);
	}
	ui->version_cb->setCurrentText(selectedProfile.mLastVersionId);
	ui->gameDir_le->setText(selectedProfile.mGameDir);

}

void KaminecLauncher::saveProfileJson()
{
    QJsonObject saveProfile;

    //生成profile的json模型

	saveProfile.insert("version",ui->version_cb->currentText().replace("(Downloaded)",""));
	saveProfile.insert("gameDir",ui->gameDir_le->text());




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
			  .arg(corePath).arg(ui->version_cb->currentText());

    auto fileItem = FileItem(QString("%1.json").arg(ui->version_cb->currentText()),
                             0,
                             QString("NULL"),
							 QString("%1/versions/%2/%2.json")
								 .arg(corePath).arg(ui->version_cb->currentText()),
                             versionList.at(ui->version_cb->currentIndex()).toMap().value("url").toUrl());
    dm->append(fileItem);
    dm->waitForFinished();

	JsonManager jm(this,ui->version_cb->currentText());

	fileItem = jm.getDownloadClientUrl();
	dmp->append(fileItem);


    auto downloadLibUrls = jm.getDownloadLibUrls();
    for(auto& i:downloadLibUrls){
		i.mPath.prepend(corePath+"/libraries/");
        //qDebug()<<i.name;
    }

	dmp->append(downloadLibUrls);

    //qDebug()<<"before";
    auto downloadAssertUrls = jm.getDownloadAssertUrls();
    //qDebug()<<"after";
    for(auto& i:downloadAssertUrls){
		i.mPath.prepend(corePath+"/assets/objects/");
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
	savesManager.addSaves();
}

void KaminecLauncher::on_deleteSaves_pb_clicked()
{
	auto index = ui->saveMgr_treeView->currentIndex();
	savesManager.deleteSaves(index.row());
}

void KaminecLauncher::on_backupSaves_pb_clicked()
{
	savesManager.backup();
}

void KaminecLauncher::startGame()
{
	Game *game;
	if(ui->isVerified_cb->isChecked()){
		game = new Game(this,this->getProfile(),Mode::Online);
	}else{
		game = new Game(this,this->getProfile(),Mode::Offline);
	}
	ui->start_pb->setText("Gaming...");
	ui->start_pb->setDisabled(true);
	connect(game,SIGNAL(finished(int)),this,SLOT(gameFinished()));
	game->start();

}

void KaminecLauncher::on_action_preference_triggered()
{
	auto preference = new Preference(this);
	preference->show();
}

void KaminecLauncher::on_profileSelect_cb_currentIndexChanged(const QString &arg1)
{
	Profile::setSelectedProfile(arg1);
	qDebug()<<"arg1:"<<arg1;

	auto profiles = Profile::fromJson();

	auto selectedProfile = profiles.value(arg1);
	ui->profileSelect_cb->setCurrentText(selectedProfile.mName);
	if(ui->version_cb->findText(selectedProfile.mLastVersionId)==-1){
		ui->version_cb->addItem(selectedProfile.mLastVersionId);
	}
	ui->version_cb->setCurrentText(selectedProfile.mLastVersionId);
	ui->gameDir_le->setText(selectedProfile.mGameDir);
}

void KaminecLauncher::on_saveProfile_pb_clicked()
{
	Profile::saveProfile(Profile(ui->profileSelect_cb->currentText(),
								 ui->version_cb->currentText(),
								 ui->gameDir_le->text()));
}

void KaminecLauncher::on_gameDir_showPb_clicked()
{
	auto gameDir = QFileDialog::getExistingDirectory(this,"Please choose the game directory.(the upper directory)");
	if(gameDir!=""){
		ui->gameDir_le->setText(gameDir + "/.minecraft");
	}
	return;
}

void KaminecLauncher::on_newProfile_pb_clicked()
{
//    auto
}
