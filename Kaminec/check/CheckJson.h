#ifndef CHECKJSON_H
#define CHECKJSON_H

#include "kits/JsonKit/JsonKit.h"
#include "messager/CheckInfo.h"

#include <QList>

class CheckJson
{
public:
	explicit CheckJson(const QString &version);

	QList<CheckInfo> getLibraryCheckInfos() const;

	CheckInfo getAssetsCheckInfo() const;

	CheckInfo getClientCheckInfo() const;

	QString getAssetsIndexId() const;

private:
	JsonKit jsonKit_;
};

#endif // CHECKJSON_H
