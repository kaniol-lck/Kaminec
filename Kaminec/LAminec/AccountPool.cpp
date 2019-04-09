#include "AccountPool.h"

#include "assistance/PathReplacer.h"
#include "assistance/utility.h"
#include "exception/Exceptions.hpp"
#include "kits/AuthKit/AuthResponse.h"

#include <QJsonDocument>
#include <QDebug>

AccountPool::AccountPool(QObject *parent) :
	QObject(parent),
	accountsFile_(PathReplacer::replace("<launcher>/accounts.json")),
	authResponse_(new AuthResponse(parent)),
	authKit_(authResponse_)
{
	model_.setColumnCount(6);
	model_.setHeaderData(Column::Playername, Qt::Horizontal, tr("Playername"));
	model_.setHeaderData(Column::Mode, Qt::Horizontal, tr("Mode"));
	model_.setHeaderData(Column::Email, Qt::Horizontal, tr("Email"));
	model_.setHeaderData(Column::Created, Qt::Horizontal, tr("Created"));
	model_.setHeaderData(Column::LastUsed, Qt::Horizontal, tr("lastUsed"));

	if(!accountsFile_.open(QIODevice::ReadWrite | QIODevice::Text))
		throw FileOpenException(accountsFile_.fileName());

	QByteArray bytes = QString::fromLocal8Bit(accountsFile_.readAll()).toUtf8();
	accountsFile_.close();

	if(bytes.isEmpty()){
		qDebug()<<"No content,auto make.";
		initAccounts();
		return;
	}

	QJsonParseError ok;
	accountsObject_ = QJsonDocument::fromJson(bytes,&ok).object();
	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(accountsFile_.fileName(), ok.errorString(), true);

	auto accountsVariant = accountsObject_.value("accounts").toVariant();
	for(const auto &it : accountsVariant.toMap()){
		auto modeStr = value(it, "mode").toString();
		GameMode mode;
		if(modeStr == "certified")
			mode = GameMode::Certified;
		else/* if(modeStr == "uncertified")*/
			mode = GameMode::Uncertified;

		Account account(value(it, "playername").toString(),
						mode,
						value(it, "email").toString(),
						value(it, "uuid").toString(),
						value(it, "accessToken").toString());
		accountsMap_.insert(account.name(), account);
		model_.appendRow(account2itemList(account));
	}

	sort(getAccountSorting(), getAccountAscending());

	auto items = model_.findItems(getSelectedAccountName(), Qt::MatchExactly, Column::Name);
	if(!items.isEmpty())
		model_.item(items.first()->row(), Column::Playername)->setCheckState(Qt::Checked);//set check state

	connect(authResponse_, &AuthResponse::validateFinished, [&](bool success){
		success_ = success;
	});
}

void AccountPool::resetLanguage()
{
	model_.setHeaderData(Column::Playername, Qt::Horizontal, tr("Playername"));
	model_.setHeaderData(Column::Mode, Qt::Horizontal, tr("Mode"));
	model_.setHeaderData(Column::Email, Qt::Horizontal, tr("Email"));
	model_.setHeaderData(Column::Created, Qt::Horizontal, tr("Created"));
	model_.setHeaderData(Column::LastUsed, Qt::Horizontal, tr("lastUsed"));
}

Account AccountPool::check(const QString &accountName) const
{
	auto account = accountsMap_.value(accountName);
	if(account.mode() == GameMode::Certified){
		validate(account);
	} else{

	}
	return account;
}

bool AccountPool::validate(const Account &account) const
{
	QByteArray data = AuthKit::kTokenStyle.arg(account.accessToken(),
											   getClientToken()).toUtf8();
	authKit_.validate(data);

	return success_;
}

void AccountPool::initAccounts()
{
	Account account;
	insertAccount(account);
	setAccountSorting("ByPlayerName");
	setAccountAscending(true);
}

QMap<QString, Account> AccountPool::getAccounts() const
{
	return accountsMap_;
}

QStandardItemModel *AccountPool::getAccountsModel()
{
	return &model_;
}

QString AccountPool::nameFromIndex(const QModelIndex &index) const
{
	return model_.item(index.row(), Column::Name)->data(Qt::DisplayRole).toString();
}

Account AccountPool::getAccount(const QString &accountName) const
{
	return accountsMap_.value(accountName);
}

bool AccountPool::containAccount(const QString &accountName) const
{
	return accountsMap_.contains(accountName);
}

void AccountPool::insertAccount(const Account &account)
{
	model_.appendRow(account2itemList(account));

	auto accounts = accountsObject_.value("accounts").toObject();
	accounts.insert(account.name(), account2object(account));
	accountsObject_.insert("accounts", accounts);
	writeToFile();

	if(accountsMap_.isEmpty())
		setSelectedAccountName(account.name());
	accountsMap_.insert(account.name(), account);
	sort(getAccountSorting(), getAccountAscending());
}

void AccountPool::removeAccount(const QString &accountName)
{
	//if the account to be removed is selected, set the first in remains as the selected
	if(getSelectedAccountName() == accountName && accountsMap_.count() > 1){
		auto items = model_.findItems(accountName, Qt::MatchExactly, Column::Name);
		if(!items.isEmpty()){
			auto row = items.first()->row()==1?2:1;
			model_.item(row, Column::Playername)->setCheckState(Qt::Checked);
			accountsObject_.insert("selectedAccountName", model_.item(row, Column::Name)->data(Qt::DisplayRole).toString());
			writeToFile();
		}
	}

	QJsonObject accounts = accountsObject_.value("accounts").toObject();
	accounts.remove(accountName);
	accountsObject_.insert("accounts", accounts);
	writeToFile();
	auto row = model_.findItems(accountName, Qt::MatchExactly, Column::Name).first()->row();
	model_.removeRow(row);
	accountsMap_.remove(accountName);
}

void AccountPool::editAccount(const QString &oldaccountName, Account newAccount)
{
	auto oldaccount = accountsMap_.take(oldaccountName);
	newAccount.setLastUsed(oldaccount.created());
	accountsMap_.insert(newAccount.name(), newAccount);

	if(accountsObject_.value("selectedAccountName").toString() == oldaccountName)
		accountsObject_.insert("selectedAccountName", newAccount.name());
	QJsonObject accounts = accountsObject_.value("accounts").toObject();
	accounts.remove(oldaccountName);
	accounts.insert(newAccount.name(), account2object(newAccount));
	accountsObject_.insert("accounts", accounts);
	writeToFile();

	model_.removeRow(model_.findItems(oldaccountName, Qt::MatchExactly, Column::Name).first()->row());
	model_.appendRow(account2itemList(newAccount));
}

void AccountPool::setSelectedAccountName(const QString &accountName)
{
	auto oldaccountName = getSelectedAccountName();
	accountsObject_.insert("selectedAccountName", QJsonValue(accountName));

	writeToFile();

	auto items = model_.findItems(oldaccountName, Qt::MatchExactly, Column::Name);
	if(!items.isEmpty())
		model_.item(items.first()->row(), Column::Playername)->setCheckState(Qt::Unchecked);//remove check state

	items = model_.findItems(accountName, Qt::MatchExactly, Column::Name);
	if(!items.isEmpty())
		model_.item(items.first()->row(), Column::Playername)->setCheckState(Qt::Checked);//set check state
}

QString AccountPool::getSelectedAccountName()
{
	if(!accountsObject_.contains("selectedAccountName")) return "";
	auto selectedAccountName = accountsObject_.value("selectedAccountName").toString();
	if(!accountsMap_.contains(selectedAccountName) && model_.rowCount() != 0){
		selectedAccountName = nameFromIndex(model_.index(0,0));
		accountsObject_.insert("selectedAccountName", QJsonValue(selectedAccountName));
		writeToFile();//set the first account as selected
	}
	return selectedAccountName;
}

void AccountPool::setClientToken(const QString &clientToken)
{
	accountsObject_.insert("clientToken", clientToken);
	writeToFile();
}

QString AccountPool::getClientToken() const
{
	return accountsObject_.value("clientToken").toString();
}

void AccountPool::setAccountSorting(QString accountSorting)
{
	auto settings = accountsObject_.value("settings").toObject();
	settings.insert("accountSorting", accountSorting);
	accountsObject_.insert("settings", settings);

	writeToFile();
}

QString AccountPool::getAccountSorting() const
{
	return accountsObject_.value("settings").toObject().value("accountAscending").toString();
}

void AccountPool::setAccountAscending(bool accountAscending)
{
	auto settings = accountsObject_.value("settings").toObject();
	settings.insert("accountAscending", accountAscending);
	accountsObject_.insert("settings", settings);

	writeToFile();
}

bool AccountPool::getAccountAscending() const
{
	return accountsObject_.value("settings").toObject().value("accountAscending").toBool();
}

QList<QStandardItem *> AccountPool::account2itemList(const Account &account)
{
	auto playernameItem = new QStandardItem(account.playername());
	auto modeItem = new QStandardItem(account.mode() == GameMode::Certified?"certified":"uncertified");
	auto emailItem = new QStandardItem(account.email());
	auto createdItem = new QStandardItem(account.created().toString(Qt::ISODateWithMs));
	auto lastUsedItem = new QStandardItem(account.lastUsed().toString(Qt::ISODateWithMs));
	auto nameItem = new QStandardItem(account.name());
	modeItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	playernameItem->setCheckable(false);
	playernameItem->setCheckState(Qt::Unchecked);

	return QList<QStandardItem*>{ playernameItem, modeItem, emailItem, createdItem, lastUsedItem, nameItem };
}

QJsonObject AccountPool::account2object(const Account &account)
{
	if(account.mode() == GameMode::Certified)
		return QJsonObject{
			{"mode", "certified"},
			{"email", account.email()},
			{"uuid", account.uuid()},
			{"accessToken", account.accessToken()},
			{"playername", account.playername()},
			{"created", account.created().toString(Qt::ISODateWithMs)},
			{"lastUsed", account.lastUsed().toString(Qt::ISODateWithMs)}
		};
	else
		return QJsonObject{
			{"mode", "uncertified"},
			{"playername", account.playername()},
			{"created", account.created().toString(Qt::ISODateWithMs)},
			{"lastUsed", account.lastUsed().toString(Qt::ISODateWithMs)}
		};
}

void AccountPool::sort(const QString &accountSorting, bool accountAscending)
{
	if(accountSorting == "byPlayerName")
		model_.sort(Column::Playername, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byMode")
		model_.sort(Column::Mode, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byEmail")
		model_.sort(Column::Email, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byCreated")
		model_.sort(Column::Created, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
	else if(accountSorting == "byLastUsed")
		model_.sort(Column::LastUsed, accountAscending?Qt::AscendingOrder:Qt::DescendingOrder);
}

void AccountPool::writeToFile()
{
	if(!accountsFile_.open(QIODevice::WriteOnly | QIODevice::Text))
		throw FileOpenException(accountsFile_.fileName());
	QTextStream out(&accountsFile_);
	auto bytes = QJsonDocument(accountsObject_).toJson();
	out<<bytes;
	accountsFile_.close();
}

void AccountPool::sortRecord(int column)
{
	if(column == Column::Playername)
		setAccountSorting("byPlayerName");
	else if(column == Column::Mode)
		setAccountSorting("byMode");
	else if(column == Column::Email)
		setAccountSorting("byEmail");
	else if(column == Column::Created)
		setAccountSorting("byCreated");
	else if(column == Column::LastUsed)
		setAccountSorting("byLastUsed");
}
