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
