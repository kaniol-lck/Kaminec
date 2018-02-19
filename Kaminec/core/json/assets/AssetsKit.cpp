#include "AssetsKit.h"

#include "assistance/utility.h"
#include "core/Path.h"

#include <stdexcept>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

AssetsKit::AssetsKit(QString assetsIndexId)
{
	QFile assetsFile(Path::indexesPath() + QString("/%1.json").arg(assetsIndexId));

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

QList<Object> AssetsKit::objects()
{
	if(!objects_){
		objects_ = std::make_shared<QList<Object>>();
		auto objectsMap = value(assetsVariant_, "objects").toMap();
		for(auto it = objectsMap.begin(); it != objectsMap.end(); it++){
			objects_->append(Object(it.key(), it.value()));
		}
	}
	return  *objects_;
}
