#include "savesmanager.h"

#include <QDebug>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileInfo>
#include <QFileDialog>
#include <QDateTime>

SavesManager::SavesManager(QObject *parent) :
    QObject(parent),
    savesFile_("./saves.json"),
	backuoDir_("./backup")
{
    model_.setColumnCount(3);
    model_.setHeaderData(0,Qt::Horizontal,"saevs name");
    model_.setHeaderData(1,Qt::Horizontal,"path");
    model_.setHeaderData(2,Qt::Horizontal,"change times");

    if(!savesFile_.open(QIODevice::ReadOnly|QIODevice::Text)){
//        QMessageBox::warning(0,"File not exist.",R"(It's no file called "saves.json".)");
        return;
    }


	QByteArray bytes = QString::fromLocal8Bit(savesFile_.readAll()).toUtf8();
    qDebug()<<bytes;
    savesFile_.close();

    QJsonParseError ok;
    QJsonDocument loadDoc = QJsonDocument::fromJson(bytes,&ok);
    if(ok.error != QJsonParseError::NoError){
        QMessageBox::warning(0,"Calculate Failed",R"("saves.json" may be crashed.)");
        qDebug()<<ok.errorString();
        return;
    }

    savesArray_ = loadDoc.array();

    for(int i=0;i!=savesArray_.size();++i){
        qDebug()<<"???";
        model_.appendRow(QList<QStandardItem*>{new QStandardItem(savesArray_.at(i).toObject().value("savesName").toString()),
                                              new QStandardItem(savesArray_.at(i).toObject().value("path").toString()),
                                              new QStandardItem(QString::number(savesArray_.at(i).toObject().value("changeTimes").toInt()))});
    }

    this->backup();
}

QStandardItemModel *SavesManager::getModel()
{
    return &model_;
}

void SavesManager::addSaves()
{
    qDebug()<<"???";
	QString savesPath = QFileDialog::getExistingDirectory
			(0,"Please choose your savesFile");
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

        savesArray_.insert(savesArray_.end(),fileInfo);

        this->writeToJson();
    }
	this->backup();
}

void SavesManager::deleteSaves(int index)
{
	if(index<savesArray_.size()){
		savesArray_.removeAt(index);
		this->writeToJson();
		model_.removeRow(index);
	}
}

bool SavesManager::backup()
{
    for(int i=0;i!=savesArray_.size();++i){
        QFileInfo savesInfo(savesArray_.at(i).toObject().value("path").toString()+"/level.dat");

        if(double(savesInfo.lastModified().toMSecsSinceEpoch())==
                savesArray_.at(i).toObject().value("lastModified").toDouble()){
            qDebug()<<"Not Modified";
        }else{
            model_.removeRow(i);
            model_.appendRow(QList<QStandardItem*>{new QStandardItem(savesArray_.at(i).toObject().value("savesName").toString()),
                                                  new QStandardItem(savesInfo.absolutePath()),
                                                  new QStandardItem(QString::number(savesArray_.at(i).toObject().value("changeTimes").toInt()))});
            qDebug()<<"Modified";
            QDir oldSaves(savesArray_.at(i).toObject().value("path").toString());
            backuoDir_.mkdir(savesArray_.at(i).toObject().value("savesName").toString());

            this->copyRecursively(oldSaves.path(),
                                  backuoDir_.path()+QString("/%1/%1_第%2次备份")
                                  .arg(savesArray_.at(i).toObject().value("savesName").toString())
                                  .arg(savesArray_.at(i).toObject().value("changeTimes").toInt()));

            QJsonObject newVersionSaves;
            newVersionSaves.insert("savesName",savesArray_.at(i).toObject().value("savesName").toString());
            newVersionSaves.insert("path",savesArray_.at(i).toObject().value("path").toString());
            newVersionSaves.insert("lastModified",savesInfo.lastModified().toMSecsSinceEpoch());
            newVersionSaves.insert("changeTimes",savesArray_.at(i).toObject().value("changeTimes").toInt()+1);

            savesArray_.removeAt(i);
            savesArray_.append(newVersionSaves);

            this->writeToJson();
        }
    }
    return true;
}

void SavesManager::writeToJson()
{
    QJsonDocument saveDoc;
    saveDoc.setArray(savesArray_);

    QByteArray bytes = saveDoc.toJson(QJsonDocument::Compact);

    qDebug()<<bytes;

    //生成profile的json文档
    savesFile_.open(QIODevice::WriteOnly|QIODevice::Text);

    QTextStream output(&savesFile_);
    output<<bytes;
    savesFile_.close();
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
