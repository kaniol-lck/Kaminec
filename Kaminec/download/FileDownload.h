#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H

#include <QObject>

class FileDownload : public QObject
{
	Q_OBJECT
public:
	explicit FileDownload(QObject *parent = nullptr);

	virtual bool exists() const = 0;
	virtual void addDownload() = 0;

signals:
	void downloadFinished();
};

#endif // FILEDOWNLOAD_H
