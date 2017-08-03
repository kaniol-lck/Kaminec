#include "profile.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>

Profile::Profile(QString name,
				 QString lastVersionId,
				 QString gameDir):
	mName(name),
	mLastVersionId(lastVersionId),
	mGameDir(gameDir)
{}

QMap<QString,Profile> Profile::fromJson()
{
	QString corePath = QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/.minecraft").toString();
	if(!QDir(corePath).exists()){
		QDir().mkpath(corePath);
	}
	QFile loadfile(corePath + "/launcher_profiles.json");

	if(!loadfile.open(QIODevice::ReadWrite|QIODevice::Text)){
		qDebug()<<R"("launcher_profiles.json" opened error.)";
		return QMap<QString,Profile>();
	}

	QByteArray bytes = QString::fromLocal8Bit(loadfile.readAll()).toUtf8();
	if(bytes.size()==0){
		qDebug()<<"No content,auto make.";
		QJsonObject json;
		json.insert("selectedProfile","(Default)");
		QJsonObject profiles;
		QJsonObject profile;
		profile.insert("name","(Default)");
		profile.insert("lastVersionId","1.10.2");
		profile.insert("gameDir",QSettings().value("corePath").toString());
		profiles.insert("(Default)",profile);
		json.insert("profiles",profiles);

		QTextStream out(&loadfile);
		bytes = QJsonDocument(json).toJson();
		out<<bytes;
	}
	loadfile.close();

	QJsonParseError ok;
	QJsonDocument loadDoc = QJsonDocument::fromJson(bytes,&ok);
	if(ok.error != QJsonParseError::NoError){
		qDebug()<<ok.errorString();
		QMessageBox::warning(0,"Calculate Failed",R"("launcher_profiles.json" may be crashed.)");
		return QMap<QString,Profile>();
	}

	auto loadProfiles = loadDoc.toVariant().toMap().value("profiles").toMap();	QMap<QString,Profile> profiles;
	for(auto profile : loadProfiles){
		profiles.insert(profile.toMap().value("name").toString(),
						Profile(profile.toMap().value("name").toString(),
								profile.toMap().value("lastVersionId").toString(),
								profile.toMap().value("gameDir").toString()));
	}

	return profiles;
}

QString Profile::getSelectedProfile()
{
	QFile loadfile(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).toString() +
				   "/launcher_profiles.json");

	if(!loadfile.open(QIODevice::ReadOnly|QIODevice::Text)){
		QMessageBox::warning(0,"File not exist.",R"(It's no file called "launcher_profiles.json".)");
		return QString();
	}

	QByteArray bytes = QString::fromLocal8Bit(loadfile.readAll()).toUtf8();
	loadfile.close();

	QJsonParseError ok;
	QJsonDocument loadDoc = QJsonDocument::fromJson(bytes,&ok);
	if(ok.error != QJsonParseError::NoError){
		qDebug()<<ok.errorString();
		QMessageBox::warning(0,"Calculate Failed",R"("launcher_profiles.json" may be crashed.)");
		return QString();
	}

	QJsonObject loadObject = loadDoc.object();

	return loadObject.value("selectedProfile").toString();
}

void Profile::setSelectedProfile(QString selectedProfile)
{
	QFile loadfile(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).toString() +
				   "/launcher_profiles.json");

	if(!loadfile.open(QIODevice::ReadOnly|QIODevice::Text)){
		qDebug()<<R"(It's no file called "launcher_profiles.json".)";
		return;
	}

	QByteArray bytes = QString::fromLocal8Bit(loadfile.readAll()).toUtf8();
	loadfile.close();

	QJsonParseError ok;
	QJsonDocument loadDoc = QJsonDocument::fromJson(bytes,&ok);
	if(ok.error != QJsonParseError::NoError){
		qDebug()<<ok.errorString();
		QMessageBox::warning(0,"Calculate Failed",R"("launcher_profiles.json" may be crashed.)");
		return;
	}

	QJsonObject loadObject = loadDoc.object();

	loadObject.insert("selectedProfile",selectedProfile);

	if(!loadfile.open(QIODevice::WriteOnly|QIODevice::Text)){
		qDebug()<<R"(It's no file called "launcher_profiles.json".)";
		return;
	}

	QTextStream out(&loadfile);
	out<<QJsonDocument(loadObject).toJson();
	loadfile.close();

	return;
}

void Profile::saveProfile(const Profile &profile)
{
	QFile loadfile(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).toString() +
				   "/launcher_profiles.json");

	if(!loadfile.open(QIODevice::ReadOnly|QIODevice::Text)){
		qDebug()<<R"(It's no file called "launcher_profiles.json".)";
		return;
	}

	QByteArray bytes = QString::fromLocal8Bit(loadfile.readAll()).toUtf8();

	loadfile.close();

	QJsonParseError ok;
	QJsonDocument loadDoc = QJsonDocument::fromJson(bytes,&ok);
	if(ok.error != QJsonParseError::NoError){
		qDebug()<<ok.errorString();
		QMessageBox::warning(0,"Calculate Failed",R"("launcher_profiles.json" may be crashed.)");
		return;
	}

	QJsonObject loadObject = loadDoc.object();

	QJsonObject profileJson;
	profileJson.insert("name",profile.mName);
	profileJson.insert("lastVersionId",profile.mLastVersionId);
	profileJson.insert("gameDir",profile.mGameDir);

	auto profiles = loadObject.value("profiles").toObject();
	profiles.insert(profile.mName,profileJson);
	loadObject.insert("profiles",profiles);

	if(!loadfile.open(QIODevice::WriteOnly|QIODevice::Text)){
		qDebug()<<R"(It's no file called "launcher_profiles.json".)";
		return;
	}

	QTextStream out(&loadfile);
	out<<QJsonDocument(loadObject).toJson();
	loadfile.close();

	return;
}

void Profile::newProfile()
{
	QFile loadfile(QSettings().value("corePath",QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)).toString() +
				   "/launcher_profiles.json");

	if(!loadfile.open(QIODevice::ReadOnly|QIODevice::Text)){
		qDebug()<<R"(It's no file called "launcher_profiles.json".)";
		return;
	}

	QByteArray bytes = QString::fromLocal8Bit(loadfile.readAll()).toUtf8();

	loadfile.close();

	QJsonParseError ok;
	QJsonDocument loadDoc = QJsonDocument::fromJson(bytes,&ok);
	if(ok.error != QJsonParseError::NoError){
		qDebug()<<ok.errorString();
		QMessageBox::warning(0,"Calculate Failed",R"("launcher_profiles.json" may be crashed.)");
		return;
	}

	QJsonObject loadObject = loadDoc.object();

	auto profiles = loadObject.value("profiles").toObject();

	QJsonObject profile;
	profile.insert("name","(Default)");
	profile.insert("lastVersionId","1.10.2");
	profile.insert("gameDir",QSettings().value("corePath").toString());
	profiles.insert("(Default)",profile);
	loadObject.insert("profiles",profiles);

	if(!loadfile.open(QIODevice::WriteOnly|QIODevice::Text)){
		qDebug()<<R"(It's no file called "launcher_profiles.json".)";
		return;
	}

	QTextStream out(&loadfile);
	out<<QJsonDocument(loadObject).toJson();
	loadfile.close();

	return;
}
