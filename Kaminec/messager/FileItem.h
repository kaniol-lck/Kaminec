#ifndef FILEITEM_H
#define FILEITEM_H

#include <QStandardItem>
#include <QList>
#include <QString>
#include <QUrl>

struct FileItem
{
    FileItem()=default;
	explicit FileItem(const QString &name,
					  const int     &size,
					  const QString &sha1,
					  const QString &path,
					  const QUrl &url);
	explicit FileItem(const QUrl &url, const QString &path);

    QList<QStandardItem *> getInfoList() const;

	QString name_;
	int   size_;
	QString Sha1_;
	QString path_;
	QUrl    url_;

};

#endif // FILEITEM_H
