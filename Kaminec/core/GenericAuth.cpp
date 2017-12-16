#include "GenericAuth.h"
#include "assistance/utility.h"

#include <QEventLoop>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QSettings>
#include <QMessageBox>

const QString GenericAuth::YggdrasilServer = "https://authserver.mojang.com";
const QString GenericAuth::authenticateStyle = R"({"agent":{"name":"Minecraft","version":1},"requestUser": false,"username":"%1","password":"%2"})";
const QString GenericAuth::tokenStyle = R"({"accessToken":"%1","clientToken":"%2"})";

const QList<QString> GenericAuth::authList = {"/authenticate",
											  "/refresh",
											  "/validate",
											  "/signout",
											  "/invalidate"};

GenericAuth::GenericAuth(QObject *parent) : QObject(parent)
{

}

void GenericAuth::authenticateFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	QByteArray data = reply->readAll();
	QJsonParseError ok;
	auto json = QJsonDocument::fromJson(data,&ok).toVariant();
	if(ok.error != QJsonParseError::NoError){qDebug()<<"AuthJson failed."<<endl<<ok.error;}

	if(statusCode == 200){
		//success
		success = true;

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

void GenericAuth::validateFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if(statusCode == 204){
		success = true;
	} else{
		success = false;
	}
}

void GenericAuth::refreshFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	QByteArray data = reply->readAll();
	QJsonParseError ok;
	auto json = QJsonDocument::fromJson(data,&ok).toVariant();
	if(ok.error != QJsonParseError::NoError){qDebug()<<"AuthJson failed."<<endl<<ok.error;}
	if(statusCode == 200){
		//success
		success = true;

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
		success = false;
		QMessageBox::warning(0,
							 value(json, "error").toString(),
							 value(json, "errorMessage").toString());

	}
}

void GenericAuth::signoutFinished(QNetworkReply */*reply*/) const
{

}

void GenericAuth::invalidateFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if(statusCode == 204){
		success = true;
	} else{
		success = false;
	}
}

void GenericAuth::sendRequest(const Authentication &authentication, const QByteArray &data) const
{
	QNetworkRequest request;

	auto endpoint = authList.at(authentication);
	request.setUrl(QUrl(YggdrasilServer + endpoint));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	QEventLoop eventloop;
	connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventloop, SLOT(quit()));
	switch (authentication) {
	case Authenticate:
		connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(authenticateFinished(QNetworkReply*)));
		break;
	case Refresh:
		connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(refreshFinished(QNetworkReply*)));
		break;
	case Validate:
		connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(validateFinished(QNetworkReply*)));
		break;
	case Signout:
		connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(signoutFinished(QNetworkReply*)));
		break;
	case Invalidate:
		connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(invalidateFinished(QNetworkReply*)));
		break;
	default:
		break;
	}
	connect(&manager,SIGNAL(finished(QNetworkReply*)),&eventloop,SLOT(quit()));

	manager.post(request, data);
	eventloop.exec();

	switch (authentication) {
	case Authenticate:
		disconnect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(authenticateFinished(QNetworkReply*)));
		break;
	case Refresh:
		disconnect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(refreshFinished(QNetworkReply*)));
		break;
	case Validate:
		disconnect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(validateFinished(QNetworkReply*)));
		break;
	case Signout:
		disconnect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(signoutFinished(QNetworkReply*)));
		break;
	case Invalidate:
		disconnect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(invalidateFinished(QNetworkReply*)));
		break;
	default:
		break;
	}
}

GenericAuth::~GenericAuth()
{/*empty implementation for abstract base class*/}
