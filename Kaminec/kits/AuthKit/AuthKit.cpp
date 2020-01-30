#include "AuthKit.h"

#include "authpayload.h"
#include "AuthResponse.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>

const QString AuthKit::kYggdrasilServer = "https://authserver.mojang.com";

AuthKit::AuthKit(AuthResponse *authResponse) :
	authResponse_(authResponse),
	manager_(new QNetworkAccessManager)
{}

void AuthKit::authenticate(const AuthenticatePayload &payload) const
{
    post(makeRequest("/authenticate"), payload, &AuthResponse::authenticateResponse);;
}

void AuthKit::validate(const ValidatePayload &payload) const
{
    post(makeRequest("/validate"), payload, &AuthResponse::validateResponse);
}

void AuthKit::refresh(const RefreshPayload &payload) const
{
    post(makeRequest("/refresh"), payload, &AuthResponse::refreshResponse);
}

void AuthKit::invalidate(const InvalidatePayload &payload) const
{
    post(makeRequest("/invalidate"), payload, &AuthResponse::invalidateResponse);
}

QNetworkRequest AuthKit::makeRequest(const QString& endpoint) const
{
	QNetworkRequest request;

	request.setUrl(QUrl(kYggdrasilServer + endpoint));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	return request;
}

template<typename SF>
void AuthKit::post(const QNetworkRequest &request, const AuthPayload &payload, SF slotFunction) const
{
	QTimer timer;
	timer.setInterval(10000);
	timer.setSingleShot(true);
	QEventLoop eventloop;
	QObject::connect(&timer, &QTimer::timeout, &eventloop, &QEventLoop::quit);
	QObject::connect(manager_.get(), &QNetworkAccessManager::finished, authResponse_, slotFunction);
	QObject::connect(manager_.get(), &QNetworkAccessManager::finished, &eventloop, &QEventLoop::quit);

    auto doc = QJsonDocument(payload.getData());
	timer.start();
    manager_->post(request, doc.toJson());
    qDebug()<<doc.toJson();
	eventloop.exec();
	qDebug() << "finished";
	if(!timer.isActive()) {
		timer.stop();
		qDebug() << "Timeout";
	}

	QObject::disconnect(manager_.get(), &QNetworkAccessManager::finished, authResponse_, slotFunction);
	QObject::disconnect(manager_.get(), &QNetworkAccessManager::finished, &eventloop, &QEventLoop::quit);
}
