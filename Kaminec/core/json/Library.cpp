#include "Library.h"

#include "core/Ruler.h"
#include "assistance/utility.h"
#include "assistance/systeminfo.h"

#include <QUrl>
#include <QDebug>

Library::Library(QVariant libraryVariant) :
	libraryVariant_(libraryVariant),
	name_(value(libraryVariant_, "name").toString()),
	nameList_(name_.split(":"))
{}

QString Library::name() const
{
	return name_;
}

QString Library::module() const
{
	return nameList_.at(0);
}

QString Library::moduleName() const
{
	return nameList_.at(1);
}

QString Library::version() const
{
	return nameList_.at(2);
}

int Library::size() const
{
	int mSize = isNatives()?value(libraryVariant_, "downloads", "classifiers", nativeKey(), "size").toInt():
								   value(libraryVariant_, "downloads", "artifact", "size").toInt();
	return mSize;
}

QString Library::sha1() const
{
	QString mSha1 = isNatives()?value(libraryVariant_, "downloads", "classifiers", nativeKey(), "sha1").toString():
									   value(libraryVariant_, "downloads", "artifact", "sha1").toString();
	return mSha1;
}

QString Library::path() const
{
	if(isNatives())
		return QString("%1/%2/%3/%2-%3-%4.jar")
				.arg(module().replace(".", "/"), moduleName(), version(), nativeKey());
	else
		return QString("%1/%2/%3/%2-%3.jar")
				.arg(module().replace(".", "/"), moduleName(), version());
}

QUrl Library::url() const
{
	QUrl mUrl = isNatives()?value(libraryVariant_, "downloads", "classifiers", nativeKey(), "url").toUrl():
								   value(libraryVariant_, "downloads", "artifact", "url").toUrl();
	return mUrl;
}

QString Library::nativeKey() const
{
	QString mNativeKey = value(libraryVariant_, "natives", sysName()).toString();
	mNativeKey.replace("${arch}", QString::number(sysWordSize()));
	return mNativeKey;
}

bool Library::isNatives() const
{
	return libraryVariant_.toMap().contains("natives") &&
			value(libraryVariant_, "natives").toMap().contains(sysName());
}

bool Library::isAllow() const
{
	if(libraryVariant_.toMap().contains("rules")){
		Ruler ruler(value(libraryVariant_, "rules"));
		return ruler.isAllow();
	}else{
		return true;
	}
}
