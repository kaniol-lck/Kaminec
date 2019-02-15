#include "accounttab.h"
#include "ui_accounttab.h"

#include "UI/accountdialog.h"

AccountTab::AccountTab(QWidget *parent, AccountPool *accountPool) :
	QWidget(parent),
	ui_(new Ui::AccountTab),
	accountPool_(accountPool)
{
	ui_->setupUi(this);
	ui_->setAccountActive_pb->setVisible(false);
	ui_->deleteAccount_pb->setVisible(false);	ui_->accounts_tableView->setModel(accountPool_->getAccountsModel());

	ui_->accounts_tableView->verticalHeader()->setDefaultSectionSize(25);
	ui_->accounts_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui_->accounts_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui_->accounts_tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
	ui_->accounts_tableView->setColumnWidth(0, 100);
	ui_->accounts_tableView->setColumnWidth(1, 50);
	ui_->accounts_tableView->horizontalHeader()->setSortIndicatorShown(true);
	ui_->accounts_tableView->hideColumn(AccountPool::Column::Uuid);
	ui_->accounts_tableView->hideColumn(AccountPool::Column::Created);
	ui_->accounts_tableView->hideColumn(AccountPool::Column::LastUsed);

	connect(ui_->accounts_tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), accountPool_, SLOT(sortRecord(int)));
	connect(ui_->accounts_tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(accountSortRecord()));


}

AccountTab::~AccountTab()
{
	delete ui_;
}

void AccountTab::on_addAccount_pb_clicked()
{
	auto accountDialog = new AccountDialog(this, accountPool_);
	accountDialog->exec();
}

void AccountTab::on_deleteAccount_pb_clicked()
{
	auto index = ui_->accounts_tableView->currentIndex();
	if(index.isValid()){
		accountPool_->removeAccount(accountPool_->uuidFromIndex(index));
	}
}

void AccountTab::on_setAccountActive_pb_clicked()
{
	accountPool_->setSelectedAccountUuid(accountPool_->uuidFromIndex(ui_->accounts_tableView->currentIndex()));
}

void AccountTab::accountSortRecord()
{
	accountPool_->setAccountAscending(ui_->accounts_tableView->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder);
}

void AccountTab::on_accounts_tableView_pressed(const QModelIndex &/*index*/)
{
	ui_->setAccountActive_pb->setVisible(true);
	ui_->deleteAccount_pb->setVisible(true);
}

void AccountTab::on_accounts_tableView_doubleClicked(const QModelIndex &index)
{
	if(index.isValid()){
		auto oldAccountUuid = accountPool_->uuidFromIndex(index);
		auto accountDialog = new AccountDialog(this, accountPool_, oldAccountUuid);
		accountDialog->exec();
	}
}
