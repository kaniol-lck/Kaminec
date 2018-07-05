#ifndef AUTHRESPONSE_H
#define AUTHRESPONSE_H

#include <QObject>
#include <QNetworkReply>

class AuthResponse : public QObject
{
	Q_OBJECT
public:
	explicit AuthResponse(QObject *parent = nullptr);

signals:
	void uuidUpdate(QString uuid) const;
	void accessTokenUpdate(QString accessToken) const;
	void clientTokenUpdate(QString clientToken) const;
	void playerNameUpdate(QString playername) const;

	void authError(QString error, QString errorMessage) const;

	void authenticateFinished(bool ok) const;
	void validateFinished(bool ok) const;
	void refreshFinished(bool ok) const;
	void signoutFinished(bool ok) const;
	void invalidateFinished(bool ok) const;

public slots:
	void authenticateResponse(QNetworkReply *reply) const;
	void validateResponse(QNetworkReply *reply) const;
	void refreshResponse(QNetworkReply *reply) const;
	void signoutResponse(QNetworkReply *reply) const;
	void invalidateResponse(QNetworkReply *reply) const;

private:
	static QVariant jsonParse(QNetworkReply *reply, const QString &exceptionTitle);

};

#endif // AUTHRESPONSE_H
