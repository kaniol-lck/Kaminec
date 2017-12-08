#ifndef SAVESMANAGER_H
#define SAVESMANAGER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QJsonArray>
#include <QStandardItemModel>

class SavesManager : public QObject
{
    Q_OBJECT
public:
	explicit SavesManager(QObject *parent);

    QStandardItemModel* getModel();
    void addSaves();
	void deleteSaves(int index);
    bool backup();

signals:

public slots:

private:
    QStandardItemModel model;
    QFile savesFile;
    QDir backuoDir;
    QJsonArray savesArray;
    void writeToJson();
	bool copyRecursively(const QString &srcFilePath, const QString &tgtFilePath);
};

#endif // SAVESMANAGER_H
