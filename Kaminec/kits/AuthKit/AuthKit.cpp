#include "AuthKit.h"

#include <QObject>
#include <QEventLoop>

const QString AuthKit::kYggdrasilServer = "https://authserver.mojang.com";
const QString AuthKit::kAuthenticateStyle = R"({"agent":{"name":"Minecraft","version":1},"requestUser": false,"username":"%1","password":"%2"})";
const QString AuthKit::kTokenStyle = R"({"accessToken":"%1","clientToken":"%2"})";

AuthKit::AuthKit(AuthResponse *authResponse) :
	authResponse_(authResponse),
	manager_(new QNetworkAccessManager)
{}

void AuthKit::authenticate(const QByteArray &data) const
{
	post(makeRequest("/authenticate"), data, SLOT(authenticateResponse(QNetworkReply*)));;
}

void AuthKit::validate(const QByteArray &data) const
{
	post(makeRequest("/validate"), data, SLOT(validateResponse(QNetworkReply*)));
}

void AuthKit::refresh(const QByteArray &data) const
{
	post(makeRequest("/refresh"), data, SLOT(refreshResponse(QNetworkReply*)));
}

void AuthKit::invalidate(const QByteArray &data) const
{
	post(makeRequest("/invalidate"), data, SLOT(invalidateResponse(QNetworkReply*)));
}

QNetworkRequest AuthKit::makeRequest(const QString& endpoint) const
{
	QNetworkRequest request;

	request.setUrl(QUrl(kYggdrasilServer + endpoint));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	return request;
}

void AuthKit::post(const QNetworkRequest &request, const QByteArray &data, const char *slotFunction) const
{
	QEventLoop eventloop;
	QObject::connect(manager_.get(), SIGNAL(finished(QNetworkReply*)), authResponse_, slotFunction);
	QObject::connect(manager_.get(), SIGNAL(finished(QNetworkReply*)), &eventloop, SLOT(quit()));

	manager_->post(request, data);
	eventloop.exec();
	QObject::disconnect(manager_.get(), SIGNAL(finished(QNetworkReply*)), authResponse_, slotFunction);
	QObject::disconnect(manager_.get(), SIGNAL(finished(QNetworkReply*)), &eventloop, SLOT(quit()));
}
