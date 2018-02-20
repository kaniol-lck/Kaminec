#ifndef ACTIVEAUTH_H
#define ACTIVEAUTH_H

#include "core/auth/AuthKit.h"

#include <QObject>
#include <QSettings>

class ActiveAuth : QObject
{
public:
	ActiveAuth(QObject *parent);
	~ActiveAuth() = default;

	bool authenticate(const QString &username, const QString &password) const;
	bool refresh() const;
	bool invalidate() const;

private:
	AuthKit authKit_;
	QSettings settings_;
};

#endif // ACTIVEAUTH_H
