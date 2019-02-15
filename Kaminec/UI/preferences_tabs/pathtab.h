#ifndef PATHTAB_H
#define PATHTAB_H

#include "assistance/Custom.h"

#include <QWidget>

namespace Ui {
	class PathTab;
}

class PathTab : public QWidget
{
	Q_OBJECT

public:
	explicit PathTab(QWidget *parent = 0);

	void accepted();

	~PathTab();

private slots:
	void on_javaPath_showPb_2_clicked();

	void on_corePath_showPb_clicked();

	void on_defaultGamePath_showPb_clicked();

	void on_versionsPath_showPb_clicked();

	void on_libsPath_showPb_clicked();

	void on_nativesPath_showPb_clicked();

	void on_assetsPath_showPb_clicked();

	void on_indexesPath_showPb_clicked();

	void on_objectsPath_showPb_clicked();

	void on_unusedModsPath_showPb_clicked();

	void on_savesBackupPath_showPb_clicked();

	void on_loggerPath_showPb_clicked();

	void on_more_pb_toggled(bool checked);

private:
	Ui::PathTab *ui_;
	Custom custom_;
};

#endif // PATHTAB_H
