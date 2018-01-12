#ifndef LIBRARY_H
#define LIBRARY_H

#include <QVariant>

class Library
{
public:
	Library(QVariant libraryObject);

	QString name() const;

	QString module() const;
	QString moduleName() const;
	QString version() const;

	int size() const;
	QString sha1() const;
	QString path() const;
	QUrl url() const;

	QString nativeKey() const;

	bool isNatives() const;
	bool isAllow() const;
private:
	QVariant mLibraryObject;
	QString mName;
	QStringList mNameList;
};

#endif // LIBRARY_H
