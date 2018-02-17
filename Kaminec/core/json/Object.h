#ifndef OBJECT_H
#define OBJECT_H

#include <QVariant>

class Object
{
public:
	Object(QString name, QVariant objectVariant);

	QString name() const;
	QString hash() const;
	int size() const;
	QString path() const;
	QString url() const;

private:
	QString name_;
	QVariant objectVariant_;
};

#endif // OBJECT_H
