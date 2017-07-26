#include "savesmanager.h"

#include <QStandardItemModel>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QDateTime>

SavesManager::SavesManager(QObject *parent) :
    QObject(parent),
    savesFile("./saves.json"),
	backuoDir("./backup")
{
    model.setColumnCount(3);
    model.setHeaderData(0,Qt::Horizontal,"saevs name");
    model.setHeaderData(1,Qt::Horizontal,"path");
    model.setHeaderData(2,Qt::Horizontal,"change times");

    if(!savesFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(0,"File not exist.",R"(It's no file called "saves.json".)");
        return;
    }


    QByteArray bytes = savesFile.readAll();
    qDebug()<<bytes;
    savesFile.close();

    //解析json
    QJsonParseError ok;
    QJsonDocument loadDoc = QJsonDocument::fromJson(bytes,&ok);
    if(ok.error != QJsonParseError::NoError){
        QMessageBox::warning(0,"Calculate Failed",R"("saves.json" may be crashed.)");
        qDebug()<<ok.errorString();
        return;
    }

    savesArray = loadDoc.array();

    for(int i=0;i!=savesArray.size();++i){
        qDebug()<<"???";
        model.appendRow(QList<QStandardItem*>{new QStandardItem(savesArray.at(i).toObject().value("savesName").toString()),
                                              new QStandardItem(savesArray.at(i).toObject().value("path").toString()),
                                              new QStandardItem(QString::number(savesArray.at(i).toObject().value("changeTimes").toInt()))});
    }

    this->backup();
}

QStandardItemModel *SavesManager::getModel()
{
    return &model;
}

void SavesManager::addSaves()
{
    qDebug()<<"???";
    QString savesPath = QFileDialog::getExistingDirectory
            (0,"Please choose your savesFile","C:/");
    QFile savesFile(savesPath+"/level.dat");
    qDebug()<<savesPath;
    if(savesFile.exists()){
        QString savesName = QDir(savesPath).dirName();
        QFileInfo savesInfo(savesFile);

        QJsonObject fileInfo;
        fileInfo.insert("savesName",savesName);
        fileInfo.insert("path",savesPath);
        fileInfo.insert("lastModified",0);
        fileInfo.insert("changeTimes",0);

        savesArray.insert(savesArray.end(),fileInfo);

        this->writeToJson();
    }
    this->backup();
}

bool SavesManager::backup()
{
    for(int i=0;i!=savesArray.size();++i){
        QFileInfo savesInfo(savesArray.at(i).toObject().value("path").toString()+"/level.dat");

        //qDebug()<<"now:"<<double(savesInfo.lastModified().toMSecsSinceEpoch());
        //qDebug()<<"last:"<<savesArray.at(i).toObject().value("lastModified").toDouble();
        if(double(savesInfo.lastModified().toMSecsSinceEpoch())==
                savesArray.at(i).toObject().value("lastModified").toDouble()){
            qDebug()<<"Not Modified";
        }else{
            model.removeRow(i);
            model.appendRow(QList<QStandardItem*>{new QStandardItem(savesArray.at(i).toObject().value("savesName").toString()),
                                                  new QStandardItem(savesInfo.absolutePath()),
                                                  new QStandardItem(QString::number(savesArray.at(i).toObject().value("changeTimes").toInt()))});
            qDebug()<<"Modified";
            QDir oldSaves(savesArray.at(i).toObject().value("path").toString());
            backuoDir.mkdir(savesArray.at(i).toObject().value("savesName").toString());

            this->copyRecursively(oldSaves.path(),
                                  backuoDir.path()+QString("/%1/%1_第%2次备份")
                                  .arg(savesArray.at(i).toObject().value("savesName").toString())
                                  .arg(savesArray.at(i).toObject().value("changeTimes").toInt()));

            QJsonObject newVersionSaves;
            newVersionSaves.insert("savesName",savesArray.at(i).toObject().value("savesName").toString());
            newVersionSaves.insert("path",savesArray.at(i).toObject().value("path").toString());
            newVersionSaves.insert("lastModified",savesInfo.lastModified().toMSecsSinceEpoch());
            newVersionSaves.insert("changeTimes",savesArray.at(i).toObject().value("changeTimes").toInt()+1);

            savesArray.removeAt(i);
            savesArray.append(newVersionSaves);

            this->writeToJson();
        }
    }
    return true;
}

void SavesManager::writeToJson()
{
    QJsonDocument saveDoc;
    saveDoc.setArray(savesArray);

    QByteArray bytes = saveDoc.toJson(QJsonDocument::Compact);

    qDebug()<<bytes;

    //生成profile的json文档
    savesFile.open(QIODevice::WriteOnly|QIODevice::Text);

    QTextStream output(&savesFile);
    output<<bytes;
    savesFile.close();
}

bool SavesManager::copyRecursively(const QString &srcFilePath, const QString &tgtFilePath)
{
    qDebug()<<"saved";
    qDebug()<<"src:"<<srcFilePath;
    qDebug()<<"tgt:"<<tgtFilePath;
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();
        if (!targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
            return false;
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString &fileName, fileNames) {
            const QString newSrcFilePath
                    = srcFilePath + QLatin1Char('/') + fileName;
            const QString newTgtFilePath
                    = tgtFilePath + QLatin1Char('/') + fileName;
            if (!this->copyRecursively(newSrcFilePath, newTgtFilePath))
                return false;
        }
    } else {
        if (!QFile::copy(srcFilePath, tgtFilePath))
            return false;
    }
    return true;
}
