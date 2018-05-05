#ifndef LOGCLEANER_H
#define LOGCLEANER_H

#include <QObject>

class LogCleaner : public QObject
{
	Q_OBJECT
public:
	explicit LogCleaner(QObject *parent = nullptr);

signals:

public slots:
	void clean();
};

#endif // LOGCLEANER_H
