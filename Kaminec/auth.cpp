#include "auth.h"
#include <QJsonDocument>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QDebug>
#include <QUrl>

Auth::Auth(QObject *parent, QPair<QString,QString> account) :
	QObject(parent),
	mUsername(account.first),
	mPassword(account.second)
{

}

QString Auth::getPlayerName()
{
	return playerName;
}

QString Auth::getUuid()
{
	return uuid;
}

QString Auth::getAccessToken()
{
	return accessToken;
}

bool Auth::check()
{
	auto manager = new QNetworkAccessManager(this);
	QNetworkRequest request;

	request.setUrl(QUrl("https://authserver.mojang.com/authenticate"));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

	QString data_str = R"({"agent":{"name":"Minecraft","version":1},"username":"%1","password":"%2"})";
	data_str = data_str.arg(mUsername).arg(mPassword);
	QByteArray data = data_str.toUtf8();
	qDebug()<<data;

	QEventLoop eventloop;
	connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
	connect(manager,SIGNAL(finished(QNetworkReply*)),&eventloop,SLOT(quit()));

	manager->post(request,data);
	eventloop.exec();
	qDebug()<<"finished auth";

	return success;
}

void Auth::replyFinished(QNetworkReply *reply)
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	qDebug()<<statusCode;
	if(statusCode==200) success = true;
	QByteArray data = reply->readAll();
	qDebug() << data;

	QJsonParseError ok;
	auto doc = QJsonDocument::fromJson(data,&ok);
	if(ok.error != QJsonParseError::NoError){qDebug()<<"AuthJson failed."<<endl<<ok.error;}

	uuid = doc.toVariant().toMap().value("selectedProfile")
						  .toMap().value("id").toString();
	accessToken = doc.toVariant().toMap().value("accessToken").toString();
	playerName = doc.toVariant().toMap().value("selectedProfile")
				 .toMap().value("name").toString();
	qDebug()<<playerName;
}
