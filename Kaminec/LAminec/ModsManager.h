#ifndef MODSMANAGER_H
#define MODSMANAGER_H

#include <QObject>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDir>

class ModsManager : public QObject
{
	Q_OBJECT
public:
	explicit ModsManager(QObject *parent = nullptr);

	void setGameDir(const QString &gameDir);

	QStandardItemModel* getModel();

	void refresh();

	void start();

signals:

public slots:

private:
	QStandardItemModel model_;
	QDir usedModsDir_;
	QDir unusedModsDir_;

	static bool move(const QString &srcFilePath, const QString &tgtFilePath);
};

#endif // MODSMANAGER_H
