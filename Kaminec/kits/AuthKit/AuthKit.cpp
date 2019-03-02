#include "AuthKit.h"

#include <QObject>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>

const QString AuthKit::kYggdrasilServer = "https://authserver.mojang.com";
const QString AuthKit::kAuthenticateStyle = R"({"agent":{"name":"Minecraft","version":1},"requestUser": false,"username":"%1","password":"%2"})";
const QString AuthKit::kTokenStyle = R"({"accessToken":"%1","clientToken":"%2"})";

AuthKit::AuthKit(AuthResponse *authResponse) :
	authResponse_(authResponse),
	manager_(new QNetworkAccessManager)
{}

void AuthKit::authenticate(const QByteArray &data) const
{
	post(makeRequest("/authenticate"), data, &AuthResponse::authenticateResponse);;
}

void AuthKit::validate(const QByteArray &data) const
{
	post(makeRequest("/validate"), data, &AuthResponse::validateResponse);
}

void AuthKit::refresh(const QByteArray &data) const
{
	post(makeRequest("/refresh"), data, &AuthResponse::refreshResponse);
}

void AuthKit::invalidate(const QByteArray &data) const
{
	post(makeRequest("/invalidate"), data, &AuthResponse::invalidateResponse);
}

QNetworkRequest AuthKit::makeRequest(const QString& endpoint) const
{
	QNetworkRequest request;

	request.setUrl(QUrl(kYggdrasilServer + endpoint));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	return request;
}

template<typename SF>
void AuthKit::post(const QNetworkRequest &request, const QByteArray &data, SF slotFunction) const
{
	QTimer timer;
	timer.setInterval(10000);
	timer.setSingleShot(true);
	QEventLoop eventloop;
	QObject::connect(&timer, &QTimer::timeout, &eventloop, &QEventLoop::quit);
	QObject::connect(manager_.get(), &QNetworkAccessManager::finished, authResponse_, slotFunction);
	QObject::connect(manager_.get(), &QNetworkAccessManager::finished, &eventloop, &QEventLoop::quit);

	timer.start();
	manager_->post(request, data);
	qDebug()<<data;
	eventloop.exec();
	qDebug() << "finished";
	if(!timer.isActive()) {
		timer.stop();
		qDebug() << "Timeout";
	}

	QObject::disconnect(manager_.get(), &QNetworkAccessManager::finished, authResponse_, slotFunction);
	QObject::disconnect(manager_.get(), &QNetworkAccessManager::finished, &eventloop, &QEventLoop::quit);
}
