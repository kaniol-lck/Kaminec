#include "fileitem.h"

#include <QStandardItem>
#include <QStringList>
#include <QPair>
#include <QList>
#include <QFileInfo>

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

FileItem::FileItem(QUrl u, QString p):
    FileItem(QFileInfo(p).fileName(),
             0,
             "NULL",
             p,
             u)
{}

FileItem::FileItem(QPair<QUrl, QString> urlBind):
    FileItem(QFileInfo(urlBind.second).fileName(),
             0,
             "NULL",
             urlBind.second,
             urlBind.first)
{}

QList<QStandardItem *> FileItem::getInfoList() const
{
    return QList<QStandardItem*>{
        new QStandardItem(name),
        new QStandardItem(QString::number(size)),
        new QStandardItem(sha1),
        new QStandardItem(path),
        new QStandardItem(url.toString())
    };
}

QPair<QUrl, QString> FileItem::getDownloadInfo() const
{
    return qMakePair(url,path);
}
