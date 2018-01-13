#include "Library.h"

#include "core/Ruler.h"
#include "assistance/utility.h"

#include <QUrl>

Library::Library(QVariant libraryVariant) :
	mLibraryVariant(libraryVariant),
	mName(value(mLibraryVariant, "name").toString()),
	mNameList(mName.split(":"))
{}

QString Library::name() const
{
	return mName;
}

QString Library::module() const
{
	return mNameList.at(0);
}

QString Library::moduleName() const
{
	return mNameList.at(1);
}

QString Library::version() const
{
	return mNameList.at(2);
}

int Library::size() const
{
	static int mSize = value(mLibraryVariant, "downloads", "size").toInt();
	return mSize;
}

QString Library::sha1() const
{
	static QString mSha1 = value(mLibraryVariant, "downloads", "sha1").toString();
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
	static QUrl mUrl = value(mLibraryVariant, "downloads", "url").toUrl();
	return mUrl;
}

QString Library::nativeKey() const
{
	static QString mNativeKey = value(mLibraryVariant, "natives", sysName()).toString();
	return mNativeKey;
}

bool Library::isNatives() const
{
	return mLibraryVariant.toMap().contains("natives");
}

bool Library::isAllow() const
{
	if(mLibraryVariant.toMap().contains("rules")){
		static Ruler ruler(value(mLibraryVariant, "rules"));
		return ruler.isAllow();
	}else{
		return true;
	}
}
