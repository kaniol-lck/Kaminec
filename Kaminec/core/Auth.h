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

	bool authenticate();
	bool refresh();
	bool validate();
	bool invalidate();

signals:

public slots:
	void replyFinished(QNetworkReply*reply);

private:
	static QNetworkRequest makeRequest(const QString &endpoint);
	void post(const QNetworkRequest& request, const QByteArray& data);

	static QString YggdrasilServer;
	static QString authenticateStyle;
	static QString tokenStyle;

	QNetworkAccessManager manager;

	bool success = false;

	QString mUsername;
	QString mPassword;

	QString playerName;
	QString uuid;
	QString accessToken;
	QString clientToken;
};

#endif // AUTH_H
