#include "fileitem.h"

#include <QStandardItem>
#include <QStringList>
#include <QPair>
#include <QList>
#include <QFileInfo>
#include <QVariant>
#include <QMap>

FileItem::FileItem(const QString &name,
                   const int &size,
                   const QString &sha1,
                   const QString &path,
                   const QUrl &url):
    name_(name),
    size_(size),
    Sha1_(sha1),
    path_(path),
    url_(url)
{}

FileItem::FileItem(const QUrl &url, const QString &path):
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
        new QStandardItem(name_),
        new QStandardItem(),
        new QStandardItem(QString::number(size_)),
        new QStandardItem(Sha1_),
        new QStandardItem(path_),
        new QStandardItem(url_.toString())
    };
}
