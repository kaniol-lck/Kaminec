#include "DownloadInfo.h"

#include <QFileInfo>

DownloadInfo::DownloadInfo(const QString &name,
				   const int &size,
				   const QString &path,
				   const QUrl &url):
    name_(name),
	size_(size),
    path_(path),
    url_(url)
{}

DownloadInfo::DownloadInfo(const QUrl &url, const QString &path):
	DownloadInfo(QFileInfo(path).fileName(),
             0,
			 path,
			 url)
{}

QList<QStandardItem *> DownloadInfo::getInfoList() const
{
    return QList<QStandardItem*>{
        new QStandardItem(name_),
        new QStandardItem(),
        new QStandardItem(QString::number(size_)),
        new QStandardItem(path_),
        new QStandardItem(url_.toString())
    };
}
