#ifndef ASSETINDEX_H
#define ASSETINDEX_H

#include <QVariant>

class AssetIndex
{
public:
	AssetIndex() = default;
	AssetIndex(QVariant assetIndexVariant);

	QString id() const;

	int size() const;
	QString sha1() const;
	QUrl url() const;

	int totalSize() const;

private:
	QVariant assetIndexVariant_;
};

#endif // ASSETINDEX_H
