#include "AccountListWidget.h"
#include "UI/accountitem.h"

#include <QVBoxLayout>

AccountListWidget::AccountListWidget(QWidget *parent, AccountPool *accountPool) :
	QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	for(auto account : accountPool->getAccounts()){
		auto accountItem = new AccountItem(this, account);
		accountItem->setMinimumSize(accountItem->size());
		accountItem->setMaximumSize(accountItem->size());
		layout->addWidget(accountItem);
	}
	this->setLayout(layout);
}
