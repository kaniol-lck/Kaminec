#include "Library.h"

#include "kits/Ruler/Ruler.h"
#include "assistance/utility.h"
#include "assistance/systeminfo.h"

#include <QUrl>
#include <QDebug>

Library::Library(const QVariant &libraryVariant) :
	libraryVariant_(libraryVariant),
	name_(value(libraryVariant_, "name").toString()),
	nameList_(name_.split(":"))
{}

QString Library::name() const
{
	return name_;
}

QString Library::package() const
{
	return nameList_.at(0);
}

QString Library::packageName() const
{
	return nameList_.at(1);
}

QString Library::version() const
{
	return nameList_.at(2);
}

int Library::size() const
{
	return isNatives()?value(libraryVariant_, "downloads", "classifiers", nativeKey(), "size").toInt():
					   value(libraryVariant_, "downloads", "artifact", "size").toInt();
}

QString Library::sha1() const
{
	return isNatives()?value(libraryVariant_, "downloads", "classifiers", nativeKey(), "sha1").toString():
					   value(libraryVariant_, "downloads", "artifact", "sha1").toString();
}

QString Library::path() const
{
	if(isNatives())
		return QString("<libraries>/%1/%2/%3/%2-%3-%4.jar")
				.arg(package().replace(".", "/"), packageName(), version(), nativeKey());
	else
		return QString("<libraries>/%1/%2/%3/%2-%3.jar")
				.arg(package().replace(".", "/"), packageName(), version());
}

QUrl Library::url() const
{
	return isNatives()?value(libraryVariant_, "downloads", "classifiers", nativeKey(), "url").toUrl():
					   value(libraryVariant_, "downloads", "artifact", "url").toUrl();
}

QString Library::nativeKey() const
{
	return value(libraryVariant_, "natives", sysName()).toString()
			.replace("${arch}", QString::number(sysWordSize()));
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
