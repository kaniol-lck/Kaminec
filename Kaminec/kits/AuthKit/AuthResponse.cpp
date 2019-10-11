#include "AuthResponse.h"

#include "assistance/utility.h"
#include "exception/Exceptions.hpp"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QMessageBox>
#include <QDebug>

AuthResponse::AuthResponse(QObject *parent) :
	QObject(parent)
{}

void AuthResponse::authenticateResponse(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	auto json = jsonParse(reply, "Authentication");

	if(statusCode == 200){
		//parse json we've got
		qDebug()<<value(json, "selectedProfile", "id").toString();
		emit uuidUpdate(value(json, "selectedProfile", "id").toString());
		emit accessTokenUpdate(value(json, "accessToken").toString());
		emit clientTokenUpdate(value(json, "clientToken").toString());
		emit playerNameUpdate(value(json, "selectedProfile", "name").toString());

		emit authenticateFinished(true);
	} else{
		//failure
		emit authError(value(json, "error").toString(),
					   value(json, "errorMessage").toString());
		emit authenticateFinished(false);

	}
}

void AuthResponse::validateResponse(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if(statusCode == 204){
		emit validateFinished(true);
	} else{
		emit validateFinished(false);
	}
}

void AuthResponse::refreshResponse(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	auto json = jsonParse(reply, "Refreshing");
	if(statusCode == 200){
		//parse json we've got
		emit uuidUpdate(value(json, "selectedProfile", "id").toString());
		emit accessTokenUpdate(value(json, "accessToken").toString());
		emit clientTokenUpdate(value(json, "clientToken").toString());
		emit playerNameUpdate(value(json, "selectedProfile", "name").toString());

		emit refreshFinished(true);
	} else{
		//failure
		emit authError(value(json, "error").toString(),
					   value(json, "errorMessage").toString());
		emit refreshFinished(false);
	}
}

void AuthResponse::signoutResponse(QNetworkReply */*reply*/) const
{
	/*No Implementation*/
}

void AuthResponse::invalidateResponse(QNetworkReply *reply) const
{
	auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if(statusCode == 204){
		emit invalidateFinished(true);
	} else{
		emit invalidateFinished(false);
	}
}

QVariant AuthResponse::jsonParse(QNetworkReply *reply, const QString &exceptionTitle)
{
	QByteArray data = reply->readAll();
	QJsonParseError ok;
	auto json = QJsonDocument::fromJson(data, &ok).toVariant();
	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(exceptionTitle, ok.errorString());
	return json;
}
