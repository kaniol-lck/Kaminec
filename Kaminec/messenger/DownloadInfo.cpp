#include "DownloadInfo.h"

#include <QFileInfo>

DownloadInfo::DownloadInfo(const QString &name,
						   const int &size,
						   const QString &path,
						   const QUrl &url,
						   const QString &type):
    name_(name),
	size_(size),
    path_(path),
	url_(url),
	type_(type)
{}

QString DownloadInfo::type() const
{
	return type_;
}

QUrl DownloadInfo::url() const
{
	return url_;
}

QString DownloadInfo::path() const
{
	return path_;
}

QString DownloadInfo::name() const
{
	return name_;
}

int DownloadInfo::size() const
{
	return size_;
}
