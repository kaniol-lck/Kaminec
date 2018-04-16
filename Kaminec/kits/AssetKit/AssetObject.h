#ifndef ASSETOBJECT_H
#define ASSETOBJECT_H

#include <QVariant>

class AssetObject
{
public:
	AssetObject(const QString &name, const QVariant &objectVariant);

	QString name() const;
	QString hash() const;
	int size() const;
	QString path() const;
	QString url() const;

private:
	QString name_;
	QVariant objectVariant_;
};

#endif // ASSETOBJECT_H
