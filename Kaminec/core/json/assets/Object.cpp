#include "Object.h"

#include "assistance/utility.h"

Object::Object(const QString &name, const QVariant &objectVariant) :
	name_(name),
	objectVariant_(objectVariant)
{}

QString Object::name() const
{
	return name_;
}

QString Object::hash() const
{
	return value(objectVariant_, "hash").toString();
}

int Object::size() const
{
	return value(objectVariant_, "size").toInt();
}

QString Object::path() const
{
	return QString("%1/%2").arg(hash().left(2), hash());
}

QString Object::url() const
{
	return QString("%1/%2").arg(hash().left(2), hash());
}
