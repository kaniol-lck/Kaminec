#include "AuthResponse.h"

#include "assistance/utility.h"


#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QSettings>
#include <QMessageBox>

AuthResponse::AuthResponse(QObject *parent) :
	QObject(parent)
{}

bool AuthResponse::success()
{
	return success_;
}

void AuthResponse::authenticateFinished(QNetworkReply *reply) const
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

void AuthResponse::validateFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if(statusCode == 204){
		success_ = true;
	} else{
		success_ = false;
	}
}

void AuthResponse::refreshFinished(QNetworkReply *reply) const
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

void AuthResponse::signoutFinished(QNetworkReply */*reply*/) const
{
	/*No Implementation*/
}

void AuthResponse::invalidateFinished(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if(statusCode == 204){
		success_ = true;
	} else{
		success_ = false;
	}
}
