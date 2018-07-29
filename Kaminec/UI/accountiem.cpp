#include "accountitem.h"
#include "ui_accountitem.h"

AccountItem::AccountItem(QWidget *parent, Account account) :
	QWidget(parent),
	ui(new Ui::AccountItem)
{
	ui->setupUi(this);
	ui->playername->setText(account.playername());
	ui->email->setText(account.email());
}

AccountItem::~AccountItem()
{
	delete ui;
}
