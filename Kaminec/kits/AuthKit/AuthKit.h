#ifndef AUTHKIT_H
#define AUTHKIT_H

#include <memory>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include "authpayload.h"

class AuthResponse;

class AuthKit
{
public:
	AuthKit(AuthResponse *authResponse);

    void authenticate(const AuthenticatePayload &payload) const;
    void validate(const ValidatePayload &payload) const;
    void refresh(const RefreshPayload &payload) const;
    void signout(const SignoutPayload &payload) const = delete;//we needn't this method currently
    void invalidate(const InvalidatePayload &payload) const;

	static const QString kYggdrasilServer;
	static const QString kAuthenticateStyle;
	static const QString kTokenStyle;

private:
	QNetworkRequest makeRequest(const QString &endpoint) const;
	template<typename SF>
    void post(const QNetworkRequest &request, const AuthPayload& payload, SF slotFunction) const;

	AuthResponse *authResponse_;
	std::shared_ptr<QNetworkAccessManager> manager_;
};

#endif // AUTHKIT_H
