#ifndef LIBRARY_H
#define LIBRARY_H

#include <QVariant>

class Library
{
public:
	Library(const QVariant &libraryVariant);

	QString name() const;

	QString package() const;
	QString packageName() const;
	QString version() const;

	QString fileName() const;
	int size() const;
	QString sha1() const;
	QString path() const;
	QUrl url() const;

	QString nativeKey() const;

	bool isNatives() const;
	bool isAllow() const;

private:
	QVariant libraryVariant_;
	QString name_;
	QStringList nameList_;
};

#endif // LIBRARY_H
