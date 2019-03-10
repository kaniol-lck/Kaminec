#ifndef DOWNLOADKIT_H
#define DOWNLOADKIT_H

#include "messenger/DownloadInfo.h"
#include "kits/DownloadKit/SingleDownload.h"
#include "messenger/DownloadPack.h"

#include <QList>
#include <QQueue>
#include <QMutex>
#include <functional>

#include <QObject>

class DownloadKit : public QObject
{
	Q_OBJECT
public:
	DownloadKit(QObject *parent = nullptr);

	void appendDownloadFile(const QString &packName, const DownloadInfo &downloadInfo);

	void spur();
signals:
	void finished(QString packName, QString fileName);

public slots:
	void singleFinished(const QString &packName, const QString &fileName);

private:
	QNetworkAccessManager manager_;
	QQueue<QPair<QString, DownloadInfo>> downloadInfoQueue_;
	QList<SingleDownload*> downloaderPool_;
	static const int downloadNumber_ = 16;

};

#endif // DOWNLOADKIT_H
