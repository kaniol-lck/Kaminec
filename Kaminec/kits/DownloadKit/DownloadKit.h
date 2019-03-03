#ifndef DOWNLOADKIT_H
#define DOWNLOADKIT_H

#include "messenger/DownloadInfo.h"
#include "kits/DownloadKit/SingleDownload.h"
#include "download/DownloadPack.h"

#include <QList>
#include <QQueue>
#include <QMutex>
#include <QStandardItemModel>
#include <functional>

#include <QObject>

class DownloadKit : public QObject
{
    Q_OBJECT
private:
	explicit DownloadKit(QObject *parent = nullptr);
	DownloadKit() = delete;
	DownloadKit(DownloadKit&) = delete;

public:
	static void init(QObject *parent);
	static DownloadKit *instance();

	void appendDownloadPack(const DownloadPack &downloadPack);
	void appendDownloadPack(const DownloadPack &downloadPack, std::function<void()> slotFuntion);

	QStandardItemModel* getModel();

	void spur();

	enum Column { FileName, FileType, Status };

signals:
	void finished();

public slots:
	void singleFinished(int row);

private:
	QNetworkAccessManager manager_;
	QQueue<DownloadInfo> downloadInfoQueue_;
	QQueue<QList<QStandardItem*>> downloadRowQueue_;

	QTime downloadTime_;
	int totalCount_ = 0;
	int downloadedCount_ = 0;

	QStandardItemModel model_;

	QList<SingleDownload*> downloaderPool_;
	static const int downloadNumber_ = 16;

	QMap<QString, std::function<void()>> slotFunctions;

	static DownloadKit *pInstance;
};

#endif // DOWNLOADKIT_H
