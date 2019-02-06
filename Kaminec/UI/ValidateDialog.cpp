#include "validatedialog.h"
#include "ui_validatedialog.h"

#include <QMessageBox>

ValidateDialog::ValidateDialog(QWidget *parent, AccountPool *accountPool) :
	QDialog(parent),
	ui_(new Ui::ValidateDialog),
	authResponse_(new AuthResponse(parent)),
	authkit_(authResponse_),
	accountPool_(accountPool)
{
	ui_->setupUi(this);
	ui_->hint_label->setText("Create Account");
	setWindowTitle("Create Account");
	this->setMinimumHeight(200);
	this->setMinimumWidth(360);
	this->setMaximumHeight(200);
	this->setMaximumWidth(360);
	ui_->password_le->setEchoMode(QLineEdit::Password);
	on_online_rb_clicked();
}

ValidateDialog::ValidateDialog(QWidget *parent, AccountPool *accountPool, const Account &account) :
	ValidateDialog(parent, accountPool)
{
	account_ = account;
	ui_->hint_label->setText("Edit Account");
	setWindowTitle("Edit Account");
	ui_->email_le->setText(account.email());
	ui_->playername_le->setText(account.playername());
	if(account.mode() == Mode::Online){
		isValidated = true;
		ui_->email_le->setEnabled(false);
		ui_->playername_label->setVisible(true);
		ui_->playername_le->setVisible(true);
		ui_->password_label->setVisible(false);
		ui_->password_le->setVisible(false);
		ui_->showPassword_pb->setVisible(false);
		ui_->log_in_out_pb->setText("&Log out");
	} else{
		ui_->offline_rb->setChecked(true);
		on_offline_rb_clicked();
	}
}

ValidateDialog::~ValidateDialog()
{
	delete ui_;
}

void ValidateDialog::on_buttonBox_accepted()
{
	auto mode = ui_->online_rb->isChecked()?Mode::Online:Mode::Offline;
	auto email = ui_->email_le->text();
	auto playerName = ui_->playername_le->text();

	Account account(mode, email, uuid_, accessToken_, clientToken_, playerName);

	if(playerName.isEmpty()){
		QMessageBox::warning(this, "Warning", "The playername cannot be empty.");
		return;
	}
	if(accountPool_->containAccount(account.id())){
		QMessageBox::warning(this, "Warning", "The account is already existed.");
		return;
	}
	accept();
	accountPool_->insertAccount(account);
	accountPool_->setSelectedAccountId(account.id());
}

void ValidateDialog::on_showPassword_pb_toggled(bool checked)
{
	if(checked){
		ui_->password_le->setEchoMode(QLineEdit::Normal);
		ui_->showPassword_pb->setText("&Hide Password");
	}else{
		ui_->password_le->setEchoMode(QLineEdit::Password);
		ui_->showPassword_pb->setText("&Show Password");
	}
}

void ValidateDialog::on_log_in_out_pb_clicked()
{
	if(isValidated){
		//Log out
		QByteArray data = AuthKit::kTokenStyle.arg(account_.accessToken(), account_.clientToken()).toUtf8();
		ui_->log_in_out_pb->setEnabled(false);
		connect(authResponse_, SIGNAL(authError(QString,QString)), this, SLOT(authError(QString,QString)));
		connect(authResponse_, SIGNAL(invalidateFinished(bool)), this, SLOT(authFinished(bool)));
		authkit_.invalidate(data);
		disconnect(authResponse_, SIGNAL(invalidateFinished(bool)), this, SLOT(authFinished(bool)));
		disconnect(authResponse_, SIGNAL(authError(QString,QString)), this, SLOT(authError(QString,QString)));

		ui_->log_in_out_pb->setEnabled(true);
		if(success_){
			ui_->email_le->setEnabled(true);
			ui_->password_label->setVisible(true);
			ui_->password_le->setVisible(true);
			ui_->showPassword_pb->setVisible(true);
			ui_->log_in_out_pb->setText("&Log in");
			ui_->playername_le->setText("");
			isValidated = false;
		} else{
			//		QMessageBox::warning(this, "Error", "");
		}
	} else{
		//Log in
		QByteArray data = AuthKit::kAuthenticateStyle.arg(ui_->email_le->text(),
														  ui_->password_le->text()).toUtf8();

		ui_->log_in_out_pb->setEnabled(false);
		connect(authResponse_, SIGNAL(authError(QString,QString)), this, SLOT(authError(QString,QString)));
		connect(authResponse_, SIGNAL(uuidUpdate(QString)), this, SLOT(uuidUpdate(QString)));
		connect(authResponse_, SIGNAL(accessTokenUpdate(QString)), this, SLOT(accessTokenUpdate(QString)));
		connect(authResponse_, SIGNAL(clientTokenUpdate(QString)), this, SLOT(clientTokenUpdate(QString)));
		connect(authResponse_, SIGNAL(playerNameUpdate(QString)), this, SLOT(playerNameUpdate(QString)));
		connect(authResponse_, SIGNAL(authenticateFinished(bool)), this, SLOT(authFinished(bool)));
		authkit_.authenticate(data);
		disconnect(authResponse_, SIGNAL(authError(QString,QString)), this, SLOT(authError(QString,QString)));
		disconnect(authResponse_, SIGNAL(uuidUpdate(QString)), this, SLOT(uuidUpdate(QString)));
		disconnect(authResponse_, SIGNAL(accessTokenUpdate(QString)), this, SLOT(accessTokenUpdate(QString)));
		disconnect(authResponse_, SIGNAL(clientTokenUpdate(QString)), this, SLOT(clientTokenUpdate(QString)));
		disconnect(authResponse_, SIGNAL(playerNameUpdate(QString)), this, SLOT(playerNameUpdate(QString)));
		disconnect(authResponse_, SIGNAL(authenticateFinished(bool)), this, SLOT(authFinished(bool)));

		ui_->log_in_out_pb->setEnabled(true);
		if(success_){
			ui_->email_le->setEnabled(false);
			ui_->password_label->setVisible(false);
			ui_->password_le->setVisible(false);
			ui_->showPassword_pb->setVisible(false);
			ui_->log_in_out_pb->setText("&Log out");
			isValidated = true;
		} else{
			//		QMessageBox::warning(this, "Error", "");
		}
	}
}

void ValidateDialog::on_online_rb_clicked()
{
	ui_->playername_le->setEnabled(false);
	ui_->email_label->setVisible(true);
	ui_->email_le->setVisible(true);
	ui_->log_in_out_pb->setVisible(true);
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

void ValidateDialog::on_offline_rb_clicked()
{
	ui_->playername_label->setVisible(true);
	ui_->playername_le->setVisible(true);
	ui_->playername_le->setEnabled(true);
	ui_->email_label->setVisible(false);
	ui_->email_le->setVisible(false);
	ui_->password_label->setVisible(false);
	ui_->password_le->setVisible(false);
	ui_->showPassword_pb->setVisible(false);
	ui_->log_in_out_pb->setVisible(false);
}

void ValidateDialog::uuidUpdate(QString uuid)
{
	uuid_ = uuid;
}

void ValidateDialog::accessTokenUpdate(QString accessToken)
{
	accessToken_ = accessToken;
}

void ValidateDialog::clientTokenUpdate(QString clientToken)
{
	clientToken_  = clientToken;
}

void ValidateDialog::playerNameUpdate(QString playername)
{
	ui_->playername_le->setText(playername);
}

void ValidateDialog::authFinished(bool ok)
{
	success_ = ok;
}

void ValidateDialog::authError(QString error, QString errorMessage)
{
	QMessageBox::warning(this, error, errorMessage);
}
