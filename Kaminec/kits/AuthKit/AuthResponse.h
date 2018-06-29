#ifndef AUTHRESPONSE_H
#define AUTHRESPONSE_H

#include <QObject>
#include <QNetworkReply>

class AuthResponse : public QObject
{
	Q_OBJECT
public:
	explicit AuthResponse(QObject *parent = nullptr);

	bool success();

signals:


public slots:
	void authenticateFinished(QNetworkReply *reply) const;
	void validateFinished(QNetworkReply *reply) const;
	void refreshFinished(QNetworkReply *reply) const;
	void signoutFinished(QNetworkReply *reply) const;
	void invalidateFinished(QNetworkReply *reply) const;

private:
	static QVariant jsonParse(QNetworkReply *reply, const QString &exceptionTitle);

private:
	mutable bool success_ = false;
};

#endif // AUTHRESPONSE_H
