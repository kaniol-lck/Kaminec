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
	explicit Auth(QObject *parent);

	QString getPlayerName();
	QString getUuid();
	QString getAccessToken();

	bool check();
	bool refresh();

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
	QString clientToken;
};

#endif // AUTH_H
