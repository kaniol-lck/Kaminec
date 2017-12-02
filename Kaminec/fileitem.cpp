#include "fileitem.h"

#include <QStandardItem>
#include <QStringList>
#include <QPair>
#include <QList>
#include <QFileInfo>
#include <QVariant>
#include <QMap>

FileItem::FileItem(QString name,
                   int size,
                   QString sha1,
                   QString path,
                   QUrl url):
    mName(name),
    mSize(size),
    mSha1(sha1),
    mPath(path),
    mUrl(url)
{}

FileItem::FileItem(QUrl url, QString path):
	FileItem(QFileInfo(path).fileName(),
             0,
             "NULL",
			 path,
			 url)
{}


FileItem FileItem::fromJson(const QString& name, const QVariant& variant)
{
	auto map = variant.toMap();
	return FileItem(name,
					map.value("size").toInt(),
					map.value("sha1").toString(),
					map.value("path").toString(),
					map.value("url").toString());
}

QList<QStandardItem *> FileItem::getInfoList() const
{
    return QList<QStandardItem*>{
        new QStandardItem(mName),
        new QStandardItem(),
        new QStandardItem(QString::number(mSize)),
        new QStandardItem(mSha1),
        new QStandardItem(mPath),
        new QStandardItem(mUrl.toString())
    };
}
