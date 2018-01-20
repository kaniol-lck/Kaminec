#include "DownloadJson.h"

#include "core/Path.h"

DownloadJson::DownloadJson(QString version) :
	jsonKit(version)
{

}

QList<FileItem> DownloadJson::getLibraryFileItems() const
{
	QList<FileItem> libraryFileItems;

	for(const auto& library : jsonKit.libraries()){
		libraryFileItems << FileItem(library.name(),
									 library.size(),
									 library.sha1(),
									 library.path(),
									 library.url());
	}
	return libraryFileItems;
}

FileItem DownloadJson::getAssetsIndexFileItem() const
{
	auto assetIndex = jsonKit.assetIndex();
	return FileItem(assetIndex.id(),
					assetIndex.size(),
					assetIndex.sha1(),
					QString("/%1.json").arg(assetIndex.id()),
					assetIndex.url());
}

FileItem DownloadJson::getClientFileItem() const
{
	auto client = jsonKit.client();
	return FileItem(jsonKit.jarName(),
					client.size(),
					client.sha1(),
					QString("/%1/%1.jar").arg(jsonKit.jarName()),
					client.url());
}

QString DownloadJson::getAssetsIndexId() const
{
	return jsonKit.assetIndex().id();
}
