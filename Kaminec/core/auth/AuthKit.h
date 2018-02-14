#ifndef AUTHKIT_H
#define AUTHKIT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class AuthKit : public QObject
{
	Q_OBJECT
public:
	explicit AuthKit(QObject *parent = nullptr);
	bool authenticate(const QByteArray& data) const;
	bool validate(const QByteArray& data) const;
	bool refresh(const QByteArray& data) const;
	bool signout(const QByteArray& data) const = delete;//we needn't this method currently
	bool invalidate(const QByteArray& data) const;

public slots:
	void authenticateFinished(QNetworkReply *reply) const;
	void validateFinished(QNetworkReply *reply) const;
	void refreshFinished(QNetworkReply *reply) const;
	void signoutFinished(QNetworkReply *reply) const;
	void invalidateFinished(QNetworkReply *reply) const;

private:
	QNetworkRequest makeRequest(const QString& endpoint) const;
	void post(const QNetworkRequest& request, const QByteArray& data, const decltype(SLOT(finished(QNetworkReply*)))& slotFunction) const;

	mutable QNetworkAccessManager manager_;
	static const QString YggdrasilServer;
	static const QString authenticateStyle;
	static const QString tokenStyle;

	mutable bool success_;
};

#endif // AUTHKIT_H
