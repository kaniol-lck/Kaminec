#ifndef GENERICAUTH_H
#define GENERICAUTH_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class GenericAuth : public QObject
{
	Q_OBJECT
public:
	explicit GenericAuth(QObject *parent = nullptr);

	virtual ~GenericAuth() = 0;

signals:

public slots:
	void authenticateFinished(QNetworkReply *reply) const;
	void validateFinished(QNetworkReply *reply);
	void refreshFinished(QNetworkReply *reply);
	void signoutFinished(QNetworkReply *reply);
	void invalidateFinished(QNetworkReply *reply);

private:
	mutable QNetworkAccessManager manager;
	static const QString YggdrasilServer;
	static const QList<QString> authList;

protected:
	enum Authentication{ Authenticate,
						 Refresh,
						 Validate,
						 Signout,//no implementation currently
						 Invalidate};

	void sendRequest(const Authentication& authentication, const QByteArray& data) const;

	static const QString authenticateStyle;
	static const QString tokenStyle;
	mutable bool success = false;
};

#endif // GENERICAUTH_H
