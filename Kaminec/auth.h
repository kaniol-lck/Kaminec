#ifndef AUTH_H
#define AUTH_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>


class Auth : public QObject
{
	Q_OBJECT
public:
	explicit Auth(QObject *parent,QPair<QString,QString> account);

	QString getPlayerName();
	QString getUuid();
	QString getAccessToken();

	bool check();

signals:

public slots:
	void replyFinished(QNetworkReply*reply);

private:
	bool success = false;

	QString mUsername;
	QString mPassword;

	QString playerName;
	QString uuid;
	QString accessToken;
};

#endif // AUTH_H
