#ifndef GAMECLIENTDOWNLOAD_H
#define GAMECLIENTDOWNLOAD_H

#include <QObject>

class GameClientDownload : public QObject
{
	Q_OBJECT
public:
	explicit GameClientDownload(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GAMECLIENTDOWNLOAD_H