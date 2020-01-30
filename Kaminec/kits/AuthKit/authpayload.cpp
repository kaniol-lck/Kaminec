#include "authpayload.h"

#include <QJsonObject>
#include <cassert>

void AuthenticatePayload::setUsername(QString username)
{
    username_ = username;
}

void AuthenticatePayload::setPassword(QString password)
{
    password_ = password;
}

void AuthenticatePayload::setClientToken(QString clientToken)
{
    clientToken_ = clientToken;
}

void AuthenticatePayload::setRequestUser(bool requestUser)
{
    requestUser_ = requestUser;
}

QJsonObject AuthenticatePayload::getData() const
{
    assert(!username_.isEmpty() && !password_.isEmpty());
    auto payload = QJsonObject{
        {"agent",
            QJsonObject{
                {"name", "Minecraft"},
                {"version", "1"}}
        },
        {"username", username_},
        {"password", password_},
        {"requestUser", requestUser_}
    };

    if(!clientToken_.isEmpty())
        payload.insert("clientToken", clientToken_);

    return payload;
}

void RefreshPayload::setAccessToken(QString accessToken)
{
    accessToken_ = accessToken;
}

void RefreshPayload::setClientToken(QString clientToken)
{
    clientToken_ = clientToken;
}

void RefreshPayload::setRequestUser(bool requestUser)
{
    requestUser_ = requestUser;
}

QJsonObject RefreshPayload::getData() const
{
    assert(!accessToken_.isEmpty() && !clientToken_.isEmpty());
    return QJsonObject{
        {"accessToken", accessToken_},
        {"clientToken", clientToken_},
        {"requestUser", requestUser_}
    };
}

void ValidatePayload::setAccessToken(QString accessToken)
{
    accessToken_ = accessToken;
}

void ValidatePayload::setClientToken(QString clientToken)
{
    clientToken_ = clientToken;
}

QJsonObject ValidatePayload::getData() const
{
    assert(!accessToken_.isEmpty() && !clientToken_.isEmpty());
    return QJsonObject{
        {"accessToken", accessToken_},
        {"clientToken", clientToken_}
    };
}

void SignoutPayload::setUsername(QString username)
{
    username_ = username;
}

void SignoutPayload::setPassword(QString password)
{
    password_ = password;
}

void SignoutPayload::setClientToken(QString clientToken)
{
    clientToken_ = clientToken;
}

void SignoutPayload::setRequestUser(bool requestUser)
{
    requestUser_ = requestUser;
}

QJsonObject SignoutPayload::getData() const
{
    assert(!username_.isEmpty() && !password_.isEmpty());
    return QJsonObject{
        {"username", username_},
        {"password", password_}
    };
}

void InvalidatePayload::setAccessToken(QString accessToken)
{
    accessToken_ = accessToken;
}

void InvalidatePayload::setClientToken(QString clientToken)
{
    clientToken_ = clientToken;
}

QJsonObject InvalidatePayload::getData() const
{
    assert(!accessToken_.isEmpty() && !clientToken_.isEmpty());
    return QJsonObject{
        {"accessToken", accessToken_},
        {"clientToken", clientToken_}
    };
}
