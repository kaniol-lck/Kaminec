#ifndef DOWNLOADINFO_H
#define DOWNLOADINFO_H

#include <QStandardItem>
#include <QList>
#include <QString>
#include <QUrl>

struct DownloadInfo
{
    DownloadInfo()=default;
	explicit DownloadInfo(const QString &name,
						  const int     &size,
						  const QString &path,
						  const QUrl &url);
	explicit DownloadInfo(const QUrl &url, const QString &path);

	QString name_;
	int   size_;
	QString path_;
	QUrl    url_;

};

#endif // DOWNLOADINFO_H
