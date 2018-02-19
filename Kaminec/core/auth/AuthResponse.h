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

public slots:
	void authenticateFinished(QNetworkReply *reply) const;
	void validateFinished(QNetworkReply *reply) const;
	void refreshFinished(QNetworkReply *reply) const;
	void signoutFinished(QNetworkReply *reply) const;
	void invalidateFinished(QNetworkReply *reply) const;

private:
	mutable bool success_;
};

#endif // AUTHRESPONSE_H
