#include "DownloadJson.h"

#include "assistance/Path.h"

DownloadJson::DownloadJson(const QString &version) :
	jsonKit_(version)
{}

QList<DownloadInfo> DownloadJson::getLibraryDownloadInfos() const
{
	QList<DownloadInfo> libraryDownloadInfos;

	for(const auto& library : jsonKit_.libraries()){
		libraryDownloadInfos << DownloadInfo(library.name(),
											 library.size(),
											 library.path(),
											 library.url());
	}
	return libraryDownloadInfos;
}

DownloadInfo DownloadJson::getAssetsIndexDownloadInfo() const
{
	auto assetIndex = jsonKit_.assetIndex();
	return DownloadInfo(assetIndex.id(),
						assetIndex.size(),
						QString("/%1.json").arg(assetIndex.id()),
						assetIndex.url());
}

DownloadInfo DownloadJson::getClientDownloadInfo() const
{
	auto client = jsonKit_.client();
	return DownloadInfo(client.name(),
						client.size(),
						client.path(),
						client.url());
}

QString DownloadJson::getAssetsIndexId() const
{
	return jsonKit_.assetIndex().id();
}
