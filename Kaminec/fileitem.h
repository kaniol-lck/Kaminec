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
    explicit FileItem(QString n,
                      int s,
                      QString sh,
                      QString p,
                      QUrl u);
    explicit FileItem(QUrl u, QString p);

    explicit FileItem(QPair<QUrl,QString> urlBind);

    QList<QStandardItem *> getInfoList();
    QPair<QUrl,QString> getDownloadInfo();

    QString name;
    int   size;
    QString sha1;
    QString path;
    QUrl    url;
};

#endif // FILEITEM_H
