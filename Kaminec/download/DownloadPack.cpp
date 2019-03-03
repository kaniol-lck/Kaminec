#include "DownloadPack.h"

DownloadPack::DownloadPack(const QString &packName, const QList<DownloadInfo> &fileList) :
	packName_(packName),
	fileList_(fileList)
{}

QString DownloadPack::packName() const
{
	return packName_;
}

QList<DownloadInfo> DownloadPack::fileList() const
{
	return fileList_;
}

QList<QList<QStandardItem*>> DownloadPack::toRowList() const
{
	QList<QList<QStandardItem*>> rowList;
	rowList.append(QList<QStandardItem*>{
						new QStandardItem(packName_),
						new QStandardItem(),
						new QStandardItem()
					});

	for(auto info : fileList_)
		rowList.append(QList<QStandardItem*>{
							new QStandardItem(info.name()),
							new QStandardItem(info.type()),
							new QStandardItem("Downloading")
						});
	return rowList;
}
