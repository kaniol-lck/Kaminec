#include "CheckJson.h"

CheckJson::CheckJson(const QString &version) :
	jsonKit_(version)
{}

QList<CheckInfo> CheckJson::getLibraryCheckInfos() const
{
	QList<CheckInfo> libraryCheckInfos;

	for(const auto& library : jsonKit_.libraries()){
		libraryCheckInfos << CheckInfo(library.name(),
									   library.size(),
									   QCryptographicHash::Sha1,
									   library.sha1(),
									   library.path());
	}
	return libraryCheckInfos;
}

CheckInfo CheckJson::getAssetsCheckInfo() const
{
	auto assetIndex = jsonKit_.assetIndex();
	return CheckInfo(assetIndex.id(),
					 assetIndex.size(),
					 QCryptographicHash::Sha1,
					 assetIndex.sha1(),
					 QString("/%1.json").arg(assetIndex.id()));
}

CheckInfo CheckJson::getClientCheckInfo() const
{
	auto client = jsonKit_.client();
	return CheckInfo(jsonKit_.jarName(),
					 client.size(),
					 QCryptographicHash::Sha1,
					 client.sha1(),
					 QString("/%1/%1.jar").arg(jsonKit_.jarName()));
}

QString CheckJson::getAssetsIndexId() const
{
	return jsonKit_.assetIndex().id();
}
