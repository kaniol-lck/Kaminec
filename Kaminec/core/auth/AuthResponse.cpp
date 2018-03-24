#include "AuthResponse.h"

#include "assistance/utility.h"
#include "core/Custom.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
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
	if(ok.error != QJsonParseError::NoError)
		throw std::runtime_error(QString("Auth json is not a valid json.").toStdString());

	if(statusCode == 200){
		//success
		success_ = true;

		//parse json we've got
		auto uuid = value(json, "selectedProfile", "id").toString();
		auto accessToken = value(json, "accessToken").toString();
		auto clientToken = value(json, "clientToken").toString();
		auto playerName = value(json, "selectedProfile", "name").toString();

		//store these information to settings
		Custom custom;
		custom.setUuid(uuid);
		custom.setAccessToken(accessToken);
		custom. setClientToken(clientToken);
		custom.setOfficialName(playerName);
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
	if(ok.error != QJsonParseError::NoError)
		throw std::runtime_error(QString("Auth json is not a valid json.").toStdString());
	if(statusCode == 200){
		//success
		success_ = true;

		//parse json we've got
		auto uuid = value(json, "selectedProfile", "id").toString();
		auto accessToken = value(json, "accessToken").toString();
		auto clientToken = value(json, "clientToken").toString();
		auto playerName = value(json, "selectedProfile", "name").toString();

		//store these information to settings
		Custom custom;
		custom.setUuid(uuid);
		custom.setAccessToken(accessToken);
		custom. setClientToken(clientToken);
		custom.setOfficialName(playerName);
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
