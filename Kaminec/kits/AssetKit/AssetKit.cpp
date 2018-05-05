#include "AssetKit.h"

#include "assistance/utility.h"
#include "assistance/Path.h"
#include "assistance/Exceptions.h"

#include <QFile>
#include <QJsonDocument>
#include <QByteArray>

AssetKit::AssetKit(const QString &assetIndexId)
{
	QFile assetsFile(Path::indexesPath() + QString("/%1.json").arg(assetIndexId));

	if(!assetsFile.exists())
		throw FileNotFoundException(assetsFile.fileName());
	if(!assetsFile.open(QIODevice::ReadOnly | QIODevice::Text))
		throw FileOpenException(assetsFile.fileName());

	QByteArray assetsBytes;
	assetsBytes.resize(assetsFile.bytesAvailable());
	assetsBytes = assetsFile.readAll();
	assetsFile.close();

	QJsonParseError ok;
	assetsVariant_ = QJsonDocument::fromJson(assetsBytes, &ok).toVariant();
	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(assetsFile.fileName(), ok.errorString(), true);

}

QList<AssetObject> AssetKit::assetObjects()
{
	if(!assetObjects_){
		assetObjects_ = std::make_shared<QList<AssetObject>>();
		auto objectsMap = value(assetsVariant_, "objects").toMap();
		for(auto it = objectsMap.begin(); it != objectsMap.end(); it++){
			assetObjects_->append(AssetObject(it.key(), it.value()));
		}
	}
	return  *assetObjects_;
}
