#include "AuthKit.h"

#include <QObject>
#include <QEventLoop>

const QString AuthKit::kYggdrasilServer = "https://authserver.mojang.com";
const QString AuthKit::kAuthenticateStyle = R"({"agent":{"name":"Minecraft","version":1},"requestUser": false,"username":"%1","password":"%2"})";
const QString AuthKit::kTokenStyle = R"({"accessToken":"%1","clientToken":"%2"})";

AuthKit::AuthKit() :
	authResponse_(new AuthResponse),
	manager_(new QNetworkAccessManager)
{}

bool AuthKit::authenticate(const QByteArray &data) const
{
	post(makeRequest("/authenticate"), data, SLOT(authenticateFinished(QNetworkReply*)));
	return authResponse_->success();
}

bool AuthKit::validate(const QByteArray &data) const
{
	post(makeRequest("/validate"), data, SLOT(validateFinished(QNetworkReply*)));
	return authResponse_->success();
}

bool AuthKit::refresh(const QByteArray &data) const
{
	post(makeRequest("/refresh"), data, SLOT(refreshFinished(QNetworkReply*)));
	return authResponse_->success();
}

bool AuthKit::invalidate(const QByteArray &data) const
{
	post(makeRequest("/invalidate"), data, SLOT(invalidateFinished(QNetworkReply*)));
	return authResponse_->success();
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
	QObject::connect(manager_.get(), SIGNAL(finished(QNetworkReply*)), authResponse_.get(), slotFunction);
	QObject::connect(manager_.get(), SIGNAL(finished(QNetworkReply*)), &eventloop, SLOT(quit()));

	manager_->post(request, data);
	eventloop.exec();
	QObject::disconnect(manager_.get(), SIGNAL(finished(QNetworkReply*)), authResponse_.get(), slotFunction);
	QObject::disconnect(manager_.get(), SIGNAL(finished(QNetworkReply*)), &eventloop, SLOT(quit()));
}
