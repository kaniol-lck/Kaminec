#ifndef ACTIVEAUTH_H
#define ACTIVEAUTH_H

#include "core/GenericAuth.h"

class ActiveAuth final: public GenericAuth
{
public:
	ActiveAuth(QObject *parent);
	~ActiveAuth() = default;

	bool authenticate(QString username, QString password) const;
	bool refresh() const;
	bool invalidate() const;

private:
};

#endif // ACTIVEAUTH_H
