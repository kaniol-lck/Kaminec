#include "fileitem.h"

#include <QStandardItem>
#include <QStringList>
#include <QPair>
#include <QList>

FileItem::FileItem(QString n,
                   int s,
                   QString sh,
                   QString p,
                   QUrl u):
    name(n),
    size(s),
    sha1(sh),
    path(p),
    url(u)
{}

QList<QStandardItem *> FileItem::getInfoList()
{
    return QList<QStandardItem*>{
        new QStandardItem(name),
        new QStandardItem(QString::number(size)),
        new QStandardItem(sha1),
        new QStandardItem(path),
        new QStandardItem(url.toString())
    };
}

QPair<QUrl, QString> FileItem::getDownloadInfo()
{
    return qMakePair(url,path);
}
