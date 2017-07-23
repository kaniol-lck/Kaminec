#include "fileitem.h"

#include <QStandardItem>
#include <QStringList>
#include <QPair>
#include <QList>
#include <QFileInfo>

FileItem::FileItem(QString name,
                   int size,
                   QString sha1,
                   QString path,
                   QUrl url):
    mName(name),
    mSize(size),
    mSha1(sha1),
    mPath(path),
    mUrl(url)
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
        new QStandardItem(mName),
        new QStandardItem(),
        new QStandardItem(QString::number(mSize)),
        new QStandardItem(mSha1),
        new QStandardItem(mPath),
        new QStandardItem(mUrl.toString())
    };
}

QPair<QUrl, QString> FileItem::getDownloadInfo() const
{
    return qMakePair(mUrl,mPath);
}
