#include "auth.h"
#include <QJsonDocument>
#include <QEventLoop>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QSettings>
#include <QDebug>
#include <QUrl>

Auth::Auth(QObject *parent, QPair<QString,QString> account) :
	QObject(parent),
	mUsername(account.first),
	mPassword(account.second)
{

}

Auth::Auth(QObject *parent)
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
	qDebug()<<"checking your accessToken..";
	auto manager = new QNetworkAccessManager(this);
	QNetworkRequest request;

	request.setUrl(QUrl("https://authserver.mojang.com/authenticate"));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

	QString data_str = R"({"agent":{"name":"Minecraft","version":1},"requestUser": false,"username":"%1","password":"%2"})";
	data_str = data_str.arg(mUsername).arg(mPassword);
	QByteArray data = data_str.toUtf8();
	qDebug()<<data;

	QEventLoop eventloop;
	connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
	connect(manager,SIGNAL(finished(QNetworkReply*)),&eventloop,SLOT(quit()));

	//post check request
	manager->post(request,data);
	eventloop.exec();

	return success;
}

bool Auth::refresh()
{
	//refresh your authentication
	qDebug()<<"refreshing your accessToken..";
	auto manager = new QNetworkAccessManager(this);
	QNetworkRequest request;

	request.setUrl(QUrl("https://authserver.mojang.com/refresh"));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

	QString data_str = R"({"accessToken":"%1","clientToken":"%2"})";
	data_str = data_str.arg(QSettings().value("accessToken").toString())
			   .arg(QSettings().value("clientToken").toString());
	QByteArray data = data_str.toUtf8();
	qDebug()<<data;

	QEventLoop eventloop;
	connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
	connect(manager,SIGNAL(finished(QNetworkReply*)),&eventloop,SLOT(quit()));

	manager->post(request,data);
	eventloop.exec();

	return success;
}

void Auth::replyFinished(QNetworkReply *reply)
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	qDebug()<<statusCode;
	QByteArray data = reply->readAll();
	qDebug() << data;

	QJsonParseError ok;
	auto doc = QJsonDocument::fromJson(data,&ok);
	if(ok.error != QJsonParseError::NoError){qDebug()<<"AuthJson failed."<<endl<<ok.error;}

	if(statusCode==200){
		success = true;
		uuid = doc.toVariant().toMap().value("selectedProfile")
			   .toMap().value("id").toString();
		accessToken = doc.toVariant().toMap().value("accessToken").toString();
		clientToken = doc.toVariant().toMap().value("clientToken").toString();
		playerName = doc.toVariant().toMap().value("selectedProfile")
					 .toMap().value("name").toString();

		QSettings().setValue("accessToken", accessToken);
		QSettings().setValue("clientToken",clientToken);
		qDebug()<<"Welcome:"<<playerName;
	}else{
		qDebug()<<"statusCode:"<<statusCode;
		QMessageBox::warning(0,
							 doc.toVariant().toMap().value("error").toString(),
							 doc.toVariant().toMap().value("errorMessage").toString());
	}
}
