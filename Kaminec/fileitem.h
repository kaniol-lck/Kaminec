#ifndef FILEITEM_H
#define FILEITEM_H

#include <QStandardItem>
#include <QList>
#include <QSize>
#include <QString>
#include <QPair>
#include <QUrl>

struct FileItem
{
    FileItem()=default;
    explicit FileItem(QString name,
                      int     size,
                      QString sha1,
                      QString path,
                      QUrl url);
	explicit FileItem(QUrl url, QString path);

	static FileItem fromJson(const QString &name, const QVariant &variant);

    QList<QStandardItem *> getInfoList() const;

    QString mName;
    int   mSize;
    QString mSha1;
    QString mPath;
    QUrl    mUrl;

};

#endif // FILEITEM_H
