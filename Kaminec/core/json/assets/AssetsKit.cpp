#include "AssetsKit.h"

#include "assistance/utility.h"
#include "core/Path.h"

#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

AssetsKit::AssetsKit(QString assetsIndexId)
{
	QFile assetsFile(Path::indexesPath() + QString("/%1.json").arg(assetsIndexId));

	if(!assetsFile.exists()){/*something here*/}
	if(!assetsFile.open(QIODevice::ReadOnly | QIODevice::Text)){/*something here*/}

	QByteArray assetsBytes;
	assetsBytes.resize(assetsFile.bytesAvailable());
	assetsBytes = assetsFile.readAll();
	assetsFile.close();

	QJsonParseError ok;
	assetsVariant_ = QJsonDocument::fromJson(assetsBytes, &ok).toVariant();
	if(ok.error != QJsonParseError::NoError){/*something here*/}

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
