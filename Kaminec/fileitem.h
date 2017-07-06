#ifndef FILEITEM_H
#define FILEITEM_H

#include <QStandardItem>
#include <QList>
#include <QSize>
#include <QString>
#include <QUrl>

struct FileItem
{
    FileItem()=default;
    explicit FileItem(QString n,
                      int s,
                      QString sh,
                      QString p,
                      QUrl u);

    QList<QStandardItem *> getInfoList();
    QPair<QUrl,QString> getDownloadInfo();

    QString name;
    int   size;
    QString CRC;
    QString path;
    QUrl    url;
};

#endif // FILEITEM_H
