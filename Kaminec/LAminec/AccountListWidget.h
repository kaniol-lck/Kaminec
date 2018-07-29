#ifndef ACCOUNTLISTWIDGET_H
#define ACCOUNTLISTWIDGET_H

#include "LAminec/AccountPool.h"

#include <QWidget>

class AccountListWidget : public QWidget
{
	Q_OBJECT
public:
	explicit AccountListWidget(QWidget *parent, AccountPool *accountPool);

signals:

public slots:
};

#endif // ACCOUNTLISTWIDGET_H
