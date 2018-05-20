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
											 library.sha1(),
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
						assetIndex.sha1(),
						QString("/%1.json").arg(assetIndex.id()),
						assetIndex.url());
}

DownloadInfo DownloadJson::getClientDownloadInfo() const
{
	auto client = jsonKit_.client();
	return DownloadInfo(jsonKit_.jarName(),
						client.size(),
						client.sha1(),
						QString("/%1/%1.jar").arg(jsonKit_.jarName()),
						client.url());
}

QString DownloadJson::getAssetsIndexId() const
{
	return jsonKit_.assetIndex().id();
}
