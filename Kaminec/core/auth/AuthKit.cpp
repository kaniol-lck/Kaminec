#include "AuthKit.h"
#include "assistance/utility.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QSettings>
#include <QMessageBox>

const QString AuthKit::YggdrasilServer = "https://authserver.mojang.com";
const QString AuthKit::authenticateStyle = R"({"agent":{"name":"Minecraft","version":1},"requestUser": false,"username":"%1","password":"%2"})";
const QString AuthKit::tokenStyle = R"({"accessToken":"%1","clientToken":"%2"})";


AuthKit::AuthKit(QObject *parent) : QObject(parent)
{}

bool AuthKit::authenticate(const QByteArray &data) const
{
	post(makeRequest("/authenticate"), data, SLOT(authenticateFinished(QNetworkReply*)));
	return success_;
}

bool AuthKit::validate(const QByteArray &data) const
{
	post(makeRequest("/validate"), data, SLOT(validateFinished(QNetworkReply*)));
	return success_;
}

bool AuthKit::refresh(const QByteArray &data) const
{
	post(makeRequest("/refresh"), data, SLOT(refreshFinished(QNetworkReply*)));
	return success_;
}

bool AuthKit::invalidate(const QByteArray &data) const
{
	post(makeRequest("/invalidate"), data, SLOT(invalidateFinished(QNetworkReply*)));
	return success_;
}

void AuthKit::authenticateFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	QByteArray data = reply->readAll();
	QJsonParseError ok;
	auto json = QJsonDocument::fromJson(data,&ok).toVariant();
	if(ok.error != QJsonParseError::NoError){qDebug()<<"AuthJson failed."<<endl<<ok.error;}

	if(statusCode == 200){
		//success
		success_ = true;

		//parse json we've got
		auto uuid = value(json, "selectedProfile", "id").toString();
		auto accessToken = value(json, "accessToken").toString();
		auto clientToken = value(json, "clientToken").toString();
		auto playerName = value(json, "selectedProfile", "name").toString();

		//store these information to settings
		QSettings settings;
		settings.setValue("uuid", uuid);
		settings.setValue("accessToken", accessToken);
		settings.setValue("clientToken", clientToken);
		settings.setValue("id", playerName);
		qDebug()<<"Welcome:"<<playerName;
	} else{
		//failure
		QMessageBox::warning(0,
							 value(json, "error").toString(),
							 value(json, "errorMessage").toString());

	}
}

void AuthKit::validateFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if(statusCode == 204){
		success_ = true;
	} else{
		success_ = false;
	}
}

void AuthKit::refreshFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	QByteArray data = reply->readAll();
	QJsonParseError ok;
	auto json = QJsonDocument::fromJson(data,&ok).toVariant();
	if(ok.error != QJsonParseError::NoError){qDebug()<<"AuthJson failed."<<endl<<ok.error;}
	if(statusCode == 200){
		//success
		success_ = true;

		//parse json we've got
		auto uuid = value(json, "selectedProfile", "id").toString();
		auto accessToken = value(json, "accessToken").toString();
		auto clientToken = value(json, "clientToken").toString();
		auto playerName = value(json, "selectedProfile", "name").toString();

		//store these information to settings
		QSettings settings;
		settings.setValue("uuid", uuid);
		settings.setValue("accessToken", accessToken);
		settings.setValue("clientToken", clientToken);
		settings.setValue("name", playerName);
		qDebug()<<"Welcome:"<<playerName;
	} else{
		//failure
		success_ = false;
		QMessageBox::warning(0,
							 value(json, "error").toString(),
							 value(json, "errorMessage").toString());

	}
}

void AuthKit::signoutFinished(QNetworkReply */*reply*/) const
{

}

void AuthKit::invalidateFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if(statusCode == 204){
		success_ = true;
	} else{
		success_ = false;
	}
}

QNetworkRequest AuthKit::makeRequest(const QString& endpoint) const
{
	QNetworkRequest request;

	request.setUrl(QUrl(YggdrasilServer + endpoint));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

	return request;
}

void AuthKit::post(const QNetworkRequest &request, const QByteArray &data, const decltype(SLOT(finished(QNetworkReply*)))& slotFunction) const
{
	QEventLoop eventloop;
	connect(&manager_, SIGNAL(finished(QNetworkReply*)), this, slotFunction);
	connect(&manager_, SIGNAL(finished(QNetworkReply*)), &eventloop, SLOT(quit()));

	manager_.post(request, data);
	eventloop.exec();
	disconnect(&manager_, SIGNAL(finished(QNetworkReply*)), this, slotFunction);
	disconnect(&manager_, SIGNAL(finished(QNetworkReply*)), &eventloop, SLOT(quit()));
}
