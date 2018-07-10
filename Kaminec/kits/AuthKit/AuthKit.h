#ifndef AUTHKIT_H
#define AUTHKIT_H

#include "kits/AuthKit/AuthResponse.h"

#include <memory>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class AuthKit
{
public:
	AuthKit(AuthResponse *authResponse);

	void authenticate(const QByteArray &data) const;
	void validate(const QByteArray &data) const;
	void refresh(const QByteArray &data) const;
	void signout(const QByteArray &data) const = delete;//we needn't this method currently
	void invalidate(const QByteArray &data) const;

	static const QString kYggdrasilServer;
	static const QString kAuthenticateStyle;
	static const QString kTokenStyle;

private:
	QNetworkRequest makeRequest(const QString &endpoint) const;
	void post(const QNetworkRequest &request, const QByteArray& data, const char *slotFunction) const;

	AuthResponse *authResponse_;
	std::shared_ptr<QNetworkAccessManager> manager_;
};

#endif // AUTHKIT_H
