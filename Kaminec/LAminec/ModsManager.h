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

	void setGameDir(QString gameDir);

	QStandardItemModel* getModel();

	void refresh();

	void start();

signals:

public slots:

private:
	QStandardItemModel model;
	QDir usedModsDir;
	QDir unusedModsDir;

	static bool move(const QString &srcFilePath, const QString &tgtFilePath);
};

#endif // MODSMANAGER_H
