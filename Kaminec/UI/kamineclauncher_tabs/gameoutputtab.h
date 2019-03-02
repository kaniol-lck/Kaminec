#ifndef GAMEOUTPUTTAB_H
#define GAMEOUTPUTTAB_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
	class GameOutputTab;
}

class GameOutputTab : public QWidget
{
	Q_OBJECT

public:
	explicit GameOutputTab(QWidget *parent, QStandardItemModel *model);

	~GameOutputTab();

private:
	Ui::GameOutputTab *ui_;
};

#endif // GAMEOUTPUTTAB_H
