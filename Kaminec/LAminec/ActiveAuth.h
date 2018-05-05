#ifndef ACTIVEAUTH_H
#define ACTIVEAUTH_H

#include "kits/AuthKit/AuthKit.h"
#include "assistance/Custom.h"

#include <QObject>

class ActiveAuth : QObject
{
public:
	ActiveAuth(QObject *parent = nullptr);

	bool authenticate(const QString &username, const QString &password) const;
	bool refresh() const;
	bool invalidate() const;

private:
	AuthKit authKit_;
	Custom custom_;
};

#endif // ACTIVEAUTH_H
