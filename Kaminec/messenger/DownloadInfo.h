#ifndef DOWNLOADINFO_H
#define DOWNLOADINFO_H

#include <QStandardItem>
#include <QList>
#include <QString>
#include <QUrl>

class DownloadInfo
{
public:
	explicit DownloadInfo(const QString &name,
						  const int     &size,
						  const QString &path,
						  const QUrl &url,
						  const QString &type);

	int size() const;
	QString name() const;
	QString path() const;
	QUrl url() const;
	QString type() const;

private:
	QString name_;
	int   size_;
	QString path_;
	QUrl    url_;
	QString type_;
};

#endif // DOWNLOADINFO_H
