#ifndef AUTHPAYLOAD_H
#define AUTHPAYLOAD_H

#include <QString>

class QJsonObject;

class AuthPayload
{
public:
    AuthPayload() = default ;
    virtual QJsonObject getData() const = 0;
};

class AuthenticatePayload : public AuthPayload
{
public:
    void setUsername(QString username);
    void setPassword(QString password);
    void setClientToken(QString clientToken);
    void setRequestUser(bool requestUser);

    QJsonObject getData() const override;

private:
    QString username_;
    QString password_;
    QString clientToken_;
    bool requestUser_ = false;
};

class RefreshPayload : public AuthPayload
{
public:
    void setAccessToken(QString accessToken);
    void setClientToken(QString clientToken);
    void setRequestUser(bool requestUser);

    QJsonObject getData() const override;

private:
    QString accessToken_;
    QString clientToken_;
    bool requestUser_ = false;
};

class ValidatePayload : public AuthPayload
{
public:
    void setAccessToken(QString accessToken);
    void setClientToken(QString clientToken);

    QJsonObject getData() const override;

private:
    QString accessToken_;
    QString clientToken_;
};

class SignoutPayload : public AuthPayload
{
public:
    void setUsername(QString username);
    void setPassword(QString password);
    void setClientToken(QString clientToken);
    void setRequestUser(bool requestUser);

    QJsonObject getData() const override;

private:
    QString username_;
    QString password_;
    QString clientToken_;
    bool requestUser_ = false;
};

class InvalidatePayload : public AuthPayload
{
public:
    void setAccessToken(QString accessToken);
    void setClientToken(QString clientToken);

    QJsonObject getData() const override;

private:
    QString accessToken_;
    QString clientToken_;
};

#endif // AUTHPAYLOAD_H
