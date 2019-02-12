#include "AccountPool.h"

#include "assistance/PathReplacer.h"
#include "assistance/utility.h"
#include "exception/Exceptions.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

AccountPool::AccountPool(QObject *parent) :
	QObject(parent),
	accountsFile_(PathReplacer::replace("<launcher>/accounts.json")),
	authResponse_(new AuthResponse(parent)),
	authKit_(authResponse_)
{
	model_.setColumnCount(6);
	model_.setHeaderData(Column::Playername, Qt::Horizontal, "playername");
	model_.setHeaderData(Column::Mode, Qt::Horizontal, "mode");
	model_.setHeaderData(Column::Email, Qt::Horizontal, "email");
	model_.setHeaderData(Column::Created, Qt::Horizontal, "created");
	model_.setHeaderData(Column::LastUsed, Qt::Horizontal, "lastUsed");

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
	for(auto it : accountsVariant.toMap()){
		auto modeStr = value(it, "mode").toString();
		::Mode mode;
		if(modeStr == "online")
			mode = Mode::Online;
		else if(modeStr == "offline")
			mode = Mode::Offline;

		Account account(value(it, "playername").toString(),
						mode,
						value(it, "email").toString(),
						value(it, "uuid").toString(),
						value(it, "accessToken").toString());
		accountsMap_.insert(account.uuid(), account);
		model_.appendRow(account2itemList(account));
	}

	sort(getAccountSorting(), getAccountAscending());

	auto items = model_.findItems(getSelectedAccountId(), Qt::MatchExactly, Column::Uuid);
	if(!items.isEmpty())
		model_.item(items.first()->row(), Column::Playername)->setCheckState(Qt::Checked);//set check state
}

Account AccountPool::check(const QString &accountId) const
{
	auto account = accountsMap_.value(accountId);
	if(account.mode() == Mode::Online){
		validate(account);
	} else{

	}
	return account;
}

bool AccountPool::validate(const Account &account) const
{
	QByteArray data = AuthKit::kTokenStyle.arg(account.accessToken(),
											   getClientToken()).toUtf8();
	connect(authResponse_, SIGNAL(validateFinished(bool)), this, SLOT(validateFinished(bool)));
	authKit_.validate(data);
	disconnect(authResponse_, SIGNAL(validateFinished(bool)), this, SLOT(validateFinished(bool)));

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

QString AccountPool::idFromIndex(const QModelIndex &index) const
{
	return model_.item(index.row(), Column::Uuid)->data(Qt::DisplayRole).toString();
}

Account AccountPool::getAccount(const QString &accountId) const
{
	return accountsMap_.value(accountId);
}

bool AccountPool::containAccount(const QString &accountId) const
{
	return accountsMap_.contains(accountId);
}

void AccountPool::insertAccount(const Account &account)
{
	model_.appendRow(account2itemList(account));

	auto accounts = accountsObject_.value("accounts").toObject();
	accounts.insert(account.uuid(), account2object(account));
	accountsObject_.insert("accounts", accounts);
	writeToFile();

	if(accountsMap_.isEmpty())
		setSelectedAccountId(account.uuid());
	accountsMap_.insert(account.uuid(), account);
	sort(getAccountSorting(), getAccountAscending());
}

void AccountPool::removeAccount(const QString &accountId)
{
	//if the account to be removed is selected, set the first in remains as the selected
	if(getSelectedAccountId() == accountId && accountsMap_.count() > 1){
		auto items = model_.findItems(accountId, Qt::MatchExactly, Column::Uuid);
		if(!items.isEmpty()){
			auto row = items.first()->row()==1?2:1;
			model_.item(row, Column::Playername)->setCheckState(Qt::Checked);
			accountsObject_.insert("selectedAccountId", model_.item(row, Column::Uuid)->data(Qt::DisplayRole).toString());
			writeToFile();
		}
	}

	QJsonObject accounts = accountsObject_.value("accounts").toObject();
	accounts.remove(accountId);
	accountsObject_.insert("accounts", accounts);
	writeToFile();
	auto row = model_.findItems(accountId, Qt::MatchExactly, Column::Uuid).first()->row();
	model_.removeRow(row);
	accountsMap_.remove(accountId);
}

void AccountPool::setSelectedAccountId(const QString &accountId)
{
	auto oldAccountId = getSelectedAccountId();
	accountsObject_.insert("selectedAccountId", QJsonValue(accountId));

	writeToFile();

	auto items = model_.findItems(oldAccountId, Qt::MatchExactly, Column::Uuid);
	if(!items.isEmpty())
		model_.item(items.first()->row(), Column::Playername)->setCheckState(Qt::Unchecked);//remove check state

	items = model_.findItems(accountId, Qt::MatchExactly, Column::Uuid);
	if(!items.isEmpty())
		model_.item(items.first()->row(), Column::Playername)->setCheckState(Qt::Checked);//set check state
}

QString AccountPool::getSelectedAccountId()
{
	if(!accountsObject_.contains("selectedAccountId")) return "";
	auto selectedAccountId = accountsObject_.value("selectedAccountId").toString();
	if(!accountsMap_.contains(selectedAccountId) && model_.rowCount() != 0){
		selectedAccountId = idFromIndex(model_.index(0,0));
		accountsObject_.insert("selectedAccountId", QJsonValue(selectedAccountId));
		writeToFile();//set the first account as selected
	}
	return selectedAccountId;
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
	auto modeItem = new QStandardItem(account.mode() == Mode::Online?"online":"offline");
	auto emailItem = new QStandardItem(account.email());
	auto createdItem = new QStandardItem(account.created().toString(Qt::ISODateWithMs));
	auto lastUsedItem = new QStandardItem(account.lastUsed().toString(Qt::ISODateWithMs));
	auto uuidItem = new QStandardItem(account.uuid());
	modeItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	playernameItem->setCheckable(false);
	playernameItem->setCheckState(Qt::Unchecked);

	return QList<QStandardItem*>{ playernameItem, modeItem, emailItem, createdItem, lastUsedItem, uuidItem };
}

QJsonObject AccountPool::account2object(const Account &account)
{
	if(account.mode() == Mode::Online)
		return QJsonObject{
			{"mode", "online"},
			{"email", account.email()},
			{"uuid", account.uuid()},
			{"accessToken", account.accessToken()},
			{"playername", account.playername()},
			{"created", account.created().toString(Qt::ISODateWithMs)},
			{"lastUsed", account.lastUsed().toString(Qt::ISODateWithMs)}
		};
	else
		return QJsonObject{
			{"mode", "offline"},
			{"email", account.email()},
			{"uuid", account.uuid()},
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

void AccountPool::validateFinished(bool success)
{
	success_ = success;
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
