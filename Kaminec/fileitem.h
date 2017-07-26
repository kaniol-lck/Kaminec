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
    explicit FileItem(QUrl u, QString p);

    FileItem(QPair<QUrl,QString> urlBind);

    QList<QStandardItem *> getInfoList() const;
    QPair<QUrl,QString> getDownloadInfo() const;

    QString mName;
    int   mSize;
    QString mSha1;
    QString mPath;
    QUrl    mUrl;

};

#endif // FILEITEM_H