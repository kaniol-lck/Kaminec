#ifndef GAMEDOWNLOADDIALOG_H
#define GAMEDOWNLOADDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
	class GameDownloadDialog;
}

class GameDownloadDialog : public QDialog
{
	Q_OBJECT

public:
	explicit GameDownloadDialog(QWidget *parent = nullptr);
	~GameDownloadDialog();

	enum Column{ Id, Type, Time, ReleaseTime, Url };

private slots:
	void loadVersions();
	void reapplyFilter();

private:
	Ui::GameDownloadDialog *ui_;
	QStandardItemModel model_;
	QSortFilterProxyModel proxyModel_;
};

#endif // GAMEDOWNLOADDIALOG_H
