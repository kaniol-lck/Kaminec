#include "accountdialog.h"
#include "ui_accountdialog.h"

#include "kits/AuthKit/AuthResponse.h"
#include "LAminec/AccountPool.h"

#include <QMessageBox>

AccountDialog::AccountDialog(QWidget *parent, AccountPool *accountPool) :
	QDialog(parent),
	ui_(new Ui::AccountDialog),
	authResponse_(new AuthResponse(parent)),
	authkit_(authResponse_),
	accountPool_(accountPool)
{
	ui_->setupUi(this);
	ui_->hint_label->setText(tr("Create Account"));
	setWindowTitle(tr("Create Account"));
	setFixedSize(360,240);
	ui_->password_le->setEchoMode(QLineEdit::Password);
	on_certified_rb_clicked();

	connect(authResponse_, &AuthResponse::authError, [&](QString error, QString errorMessage){QMessageBox::warning(this, error, errorMessage);});
    connect(authResponse_, &AuthResponse::authenticateFinished, [&](bool ok){success_ = ok;});
	connect(authResponse_, &AuthResponse::uuidUpdate, [&](QString uuid){uuid_ = uuid;});
	connect(authResponse_, &AuthResponse::accessTokenUpdate, [&](QString accessToken){accessToken_ = accessToken;});
    connect(authResponse_, &AuthResponse::clientTokenUpdate, [&](QString clientToken){accountPool_->setClientToken(clientToken);});
    connect(authResponse_, &AuthResponse::playerNameUpdate, [&](QString playername){playername_ = playername;});
}

AccountDialog::AccountDialog(QWidget *parent, AccountPool *accountPool, const QString &accountName) :
	AccountDialog(parent, accountPool)
{
	oldAccount_ = std::make_shared<Account>(accountPool_->getAccount(accountName));
	ui_->hint_label->setText(tr("Edit Account"));
	setWindowTitle(tr("Edit Account"));
	ui_->email_le->setText(oldAccount_->email());
	ui_->playername_le->setText(oldAccount_->playername());
	if(oldAccount_->mode() == GameMode::Certified){
		isValidated = true;
		uuid_ = oldAccount_->uuid();
		accessToken_ = oldAccount_->accessToken();
		clientToken_ = accountPool_->getClientToken();
		ui_->email_le->setEnabled(false);
		ui_->playername_label->setVisible(true);
		ui_->playername_le->setVisible(true);
		ui_->password_label->setVisible(false);
		ui_->password_le->setVisible(false);
		ui_->showPassword_pb->setVisible(false);
	} else{
		ui_->uncertified_rb->setChecked(true);
		on_uncertified_rb_clicked();
	}
}

AccountDialog::~AccountDialog()
{
	delete ui_;
}

void AccountDialog::on_buttonBox_accepted()
{
	GameMode mode = ui_->certified_rb->isChecked()?GameMode::Certified:GameMode::Uncertified;
	QString email = ui_->email_le->text();
	QString playerName = ui_->playername_le->text();
	QString uuid;
    QString accessToken;

	if(mode == GameMode::Uncertified){
        if(playerName.isEmpty()){
            QMessageBox::warning(this, tr("Warning"), tr("The playername cannot be empty."));
            return;
        }
		uuid = "";
	} else{

        setEnabled(false);
        //Log in
        QByteArray data = AuthKit::kAuthenticateStyle.arg(ui_->email_le->text(),
                                                          ui_->password_le->text()).toUtf8();

        authkit_.authenticate(data);
        //wait for authentication...
        qDebug()<<success_;
        if(success_){
            Account account(playername_, mode, email, uuid_, accessToken_);
            if(accountPool_->containAccount(account.name())){
                QMessageBox::warning(this, tr("Warning"), tr("The account already exists."));
                return;
            }
            accountPool_->insertAccount(account);
            accept();
            return;
        } else{
            return;
        }
    }

	Account account(playerName, mode, email, uuid_, accessToken_);

	if(oldAccount_){
		accountPool_->editAccount(oldAccount_->name(), account);
	} else{
		if(accountPool_->containAccount(account.name())){
			QMessageBox::warning(this, tr("Warning"), tr("The account already exists."));
			return;
		}
		accountPool_->insertAccount(account);
	}
	accept();
	return;
}

void AccountDialog::on_showPassword_pb_toggled(bool checked)
{
	if(checked){
		ui_->password_le->setEchoMode(QLineEdit::Normal);
		ui_->showPassword_pb->setText(tr("Hide Password"));
	}else{
		ui_->password_le->setEchoMode(QLineEdit::Password);
		ui_->showPassword_pb->setText(tr("Show Password"));
	}
}

void AccountDialog::on_certified_rb_clicked()
{
	ui_->playername_le->setEnabled(false);
	ui_->email_label->setVisible(true);
	ui_->email_le->setVisible(true);
	if(!isValidated){
		ui_->playername_label->setVisible(false);
		ui_->playername_le->setVisible(false);
		ui_->password_label->setVisible(true);
		ui_->password_le->setVisible(true);
		ui_->showPassword_pb->setVisible(true);
	} else{
		ui_->playername_label->setVisible(true);
		ui_->playername_le->setVisible(true);
	}
}

void AccountDialog::on_uncertified_rb_clicked()
{
	ui_->playername_label->setVisible(true);
	ui_->playername_le->setVisible(true);
	ui_->playername_le->setEnabled(true);
	ui_->email_label->setVisible(false);
	ui_->email_le->setVisible(false);
	ui_->password_label->setVisible(false);
	ui_->password_le->setVisible(false);
	ui_->showPassword_pb->setVisible(false);
}
