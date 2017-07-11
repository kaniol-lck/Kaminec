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
    FileItem(QString n,
                      int s,
                      QString sh,
                      QString p,
                      QUrl u);
    FileItem(QUrl u, QString p);

    FileItem(QPair<QUrl,QString> urlBind);

    QList<QStandardItem *> getInfoList() const;
    QPair<QUrl,QString> getDownloadInfo() const;

    QString name;
    int   size;
    QString sha1;
    QString path;
    QUrl    url;
};

#endif // FILEITEM_H
