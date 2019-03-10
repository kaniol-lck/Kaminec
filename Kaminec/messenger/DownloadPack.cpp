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
