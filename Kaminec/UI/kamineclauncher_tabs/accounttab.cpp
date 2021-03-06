#include "accounttab.h"
#include "ui_accounttab.h"

#include "UI/dialogs/accountdialog.h"
#include "LAminec/AccountPool.h"

AccountTab::AccountTab(QWidget *parent, AccountPool *accountPool) :
	QWidget(parent),
	ui_(new Ui::AccountTab),
	accountPool_(accountPool)
{
	ui_->setupUi(this);
	ui_->setAccountActive_pb->setEnabled(false);
	ui_->deleteAccount_pb->setEnabled(false);
	ui_->accounts_tableView->setModel(accountPool_->getAccountsModel());

	ui_->accounts_tableView->verticalHeader()->setDefaultSectionSize(40);
	ui_->accounts_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui_->accounts_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui_->accounts_tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
	ui_->accounts_tableView->setColumnWidth(0, 200);
	ui_->accounts_tableView->setColumnWidth(1, 100);
	ui_->accounts_tableView->horizontalHeader()->setSortIndicatorShown(true);
	ui_->accounts_tableView->hideColumn(AccountPool::Column::Name);
	ui_->accounts_tableView->hideColumn(AccountPool::Column::Created);
	ui_->accounts_tableView->hideColumn(AccountPool::Column::LastUsed);

	auto font = ui_->accounts_tableView->horizontalHeader()->font();
	font.setPointSize(13);
	ui_->accounts_tableView->horizontalHeader()->setFont(font);

	connect(ui_->accounts_tableView->horizontalHeader(), &QHeaderView::sectionClicked, accountPool_, &AccountPool::sortRecord);
	connect(ui_->accounts_tableView->horizontalHeader(), &QHeaderView::sectionClicked, [&]()
	{
		accountPool_->setAccountAscending(ui_->accounts_tableView->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder);
	});
}

AccountTab::~AccountTab()
{
	delete ui_;
}

void AccountTab::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::LanguageChange){
		ui_->retranslateUi(this);
		accountPool_->resetLanguage();
	}else
		QWidget::changeEvent(event);
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
		accountPool_->removeAccount(accountPool_->nameFromIndex(index));
	}
}

void AccountTab::on_setAccountActive_pb_clicked()
{
	accountPool_->setSelectedAccountName(accountPool_->nameFromIndex(ui_->accounts_tableView->currentIndex()));
}

void AccountTab::on_accounts_tableView_pressed(const QModelIndex &/*index*/)
{
	ui_->setAccountActive_pb->setEnabled(true);
	ui_->deleteAccount_pb->setEnabled(true);
}

void AccountTab::on_accounts_tableView_doubleClicked(const QModelIndex &index)
{
	if(index.isValid()){
		auto oldaccountName = accountPool_->nameFromIndex(index);
		if(index.column() == 0){
			accountPool_->setSelectedAccountName(oldaccountName);
		} else{
//			auto accountDialog = new AccountDialog(this, accountPool_, oldaccountName);
//			accountDialog->exec();
		}
	}
}
