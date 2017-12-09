#include "auth.h"
#include "assistance/utility.h"
#include "Gamemode.h"
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

QString Auth::YggdrasilServer = "https://authserver.mojang.com";
QString Auth::authenticateStyle = R"({"agent":{"name":"Minecraft","version":1},"requestUser": false,"username":"%1","password":"%2"})";
QString Auth::tokenStyle = R"({"accessToken":"%1","clientToken":"%2"})";

Auth::Auth(QObject *parent, QPair<QString,QString> account) :
	QObject(parent),
	mUsername(account.first),
	mPassword(account.second)
{
	connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

Auth::Auth(QObject *parent, Mode mode) :
	QObject(parent),
	authMode(mode)
{
	connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

Auth::Auth(QObject *parent) :
	QObject(parent)
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

bool Auth::authenticate()
{
	QByteArray data = authenticateStyle.arg(mUsername).arg(mPassword).toUtf8();

	this->post(makeRequest("/authenticate"), data);
	return success;
}

bool Auth::refresh()
{
	QByteArray data = tokenStyle.arg(QSettings().value("accessToken").toString())
					  .arg(QSettings().value("clientToken").toString()).toUtf8();

	this->post(makeRequest("/refresh"), data);
	return success;
}

bool Auth::validate()
{
	QByteArray data = tokenStyle.arg(QSettings().value("accessToken").toString())
					  .arg(QSettings().value("clientToken").toString()).toUtf8();

	this->post(makeRequest("/validate"), data);
	return success;
}

bool Auth::invalidate()
{
	QByteArray data = tokenStyle.arg(QSettings().value("accessToken").toString())
					  .arg(QSettings().value("clientToken").toString()).toUtf8();

	this->post(makeRequest("/invalidate"), data);
	return success;
}

void Auth::replyFinished(QNetworkReply *reply)
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	qDebug()<<statusCode;
	QByteArray data = reply->readAll();
	qDebug() << data;

	if(statusCode == 200){
		success = true;

		QJsonParseError ok;
		auto doc = QJsonDocument::fromJson(data,&ok);
		if(ok.error != QJsonParseError::NoError){qDebug()<<"AuthJson failed."<<endl<<ok.error;}

		uuid = doc.toVariant().toMap().value("selectedProfile")
			   .toMap().value("id").toString();
		accessToken = value(doc.toVariant(), "accessToken").toString();
		clientToken = value(doc.toVariant(), "clientToken").toString();
		playerName = value(doc.toVariant(), "selectedProfile", "name").toString();

		QSettings().setValue("uuid", uuid);
		QSettings().setValue("accessToken", accessToken);
		QSettings().setValue("clientToken", clientToken);
		qDebug()<<"Welcome:"<<playerName;
	}else if(statusCode == 204){
		success = true;
		uuid = QSettings().value("uuid").toString();
		accessToken = QSettings().value("accessToken").toString();
		playerName = QSettings().value("playerName").toString();
	}else{
		QJsonParseError ok;
		auto doc = QJsonDocument::fromJson(data,&ok);
		if(ok.error != QJsonParseError::NoError){qDebug()<<"AuthJson failed."<<endl<<ok.error;}

		qDebug()<<"statusCode:"<<statusCode;
		QMessageBox::warning(0,
							 value(doc.toVariant(), "error").toString(),
							 value(doc.toVariant(), "errorMessage").toString());
	}
}

QNetworkRequest Auth::makeRequest(const QString& endpoint)
{
	QNetworkRequest request;

	request.setUrl(QUrl(YggdrasilServer + endpoint));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

	return request;
}

void Auth::post(const QNetworkRequest &request, const QByteArray &data)
{
	QEventLoop eventloop;
	connect(&manager,SIGNAL(finished(QNetworkReply*)),&eventloop,SLOT(quit()));

	manager.post(request, data);
	eventloop.exec();
	disconnect(&manager,SIGNAL(finished(QNetworkReply*)),&eventloop,SLOT(quit()));

}

Mode Auth::getMode() const
{
	return authMode;
}
