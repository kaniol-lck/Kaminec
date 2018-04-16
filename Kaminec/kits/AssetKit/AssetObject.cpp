#include "AssetObject.h"

#include "assistance/utility.h"

AssetObject::AssetObject(const QString &name, const QVariant &objectVariant) :
	name_(name),
	objectVariant_(objectVariant)
{}

QString AssetObject::name() const
{
	return name_;
}

QString AssetObject::hash() const
{
	return value(objectVariant_, "hash").toString();
}

int AssetObject::size() const
{
	return value(objectVariant_, "size").toInt();
}

QString AssetObject::path() const
{
	return QString("%1/%2").arg(hash().left(2), hash());
}

QString AssetObject::url() const
{
	return QString("%1/%2").arg(hash().left(2), hash());
}
