#ifndef DOWNLOADPACK_H
#define DOWNLOADPACK_H

#include "messenger/DownloadInfo.h"

#include <QList>
#include <QString>
#include <QStandardItem>

class DownloadPack
{
public:
	DownloadPack(const QString &packName, const QList<DownloadInfo> &fileList);

	QString packName() const;
	QList<DownloadInfo> fileList() const;

private:
	QString packName_;
	QList<DownloadInfo> fileList_;

};

#endif // DOWNLOADPACK_H
