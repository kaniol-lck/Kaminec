#ifndef AUTHKIT_H
#define AUTHKIT_H

#include "core/auth/AuthResponse.h"

#include <memory>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class AuthKit
{
public:
	AuthKit() = default;

	bool authenticate(const QByteArray& data) const;
	bool validate(const QByteArray& data) const;
	bool refresh(const QByteArray& data) const;
	bool signout(const QByteArray& data) const = delete;//we needn't this method currently
	bool invalidate(const QByteArray& data) const;

	static const QString kYggdrasilServer;
	static const QString kAuthenticateStyle;
	static const QString kTokenStyle;

private:
	QNetworkRequest makeRequest(const QString& endpoint) const;
	void post(const QNetworkRequest& request, const QByteArray& data, const decltype(SLOT(finished(QNetworkReply*)))& slotFunction) const;

	std::shared_ptr<AuthResponse> authResponse_;
	std::shared_ptr<QNetworkAccessManager> manager_;
};

#endif // AUTHKIT_H
