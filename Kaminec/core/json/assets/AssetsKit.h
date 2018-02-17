#ifndef ASSETSKIT_H
#define ASSETSKIT_H

#include "core/json/assets/Object.h"

#include <memory>
#include <QVariant>
#include <QList>

class AssetsKit
{
public:
	AssetsKit(QString assetsIndexId);

	QList<Object> objects();

private:
	QVariant assetsVariant_;

	mutable std::shared_ptr<QList<Object>> objects_;

};

#endif // ASSETSKIT_H
