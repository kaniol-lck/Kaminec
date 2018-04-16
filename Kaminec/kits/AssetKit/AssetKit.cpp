#include "AssetKit.h"

#include "assistance/utility.h"
#include "assistance/Path.h"

#include <stdexcept>
#include <QFile>
#include <QJsonDocument>
#include <QByteArray>

AssetKit::AssetKit(const QString &assetIndexId)
{
	QFile assetsFile(Path::indexesPath() + QString("/%1.json").arg(assetIndexId));

	if(!assetsFile.exists())
		throw std::runtime_error(QString("Assets json file(%1) does not exist.").arg(assetsFile.fileName()).toStdString());
	if(!assetsFile.open(QIODevice::ReadOnly | QIODevice::Text))
		throw std::runtime_error(QString("Could not be open Assets json file(%1).").arg(assetsFile.fileName()).toStdString());

	QByteArray assetsBytes;
	assetsBytes.resize(assetsFile.bytesAvailable());
	assetsBytes = assetsFile.readAll();
	assetsFile.close();

	QJsonParseError ok;
	assetsVariant_ = QJsonDocument::fromJson(assetsBytes, &ok).toVariant();
	if(ok.error != QJsonParseError::NoError)
		throw std::runtime_error(QString("Assets json file(%1) is not a valid json.").arg(assetsFile.fileName()).toStdString());

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
