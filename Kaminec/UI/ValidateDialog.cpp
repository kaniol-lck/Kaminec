#include "validatedialog.h"
#include "ui_validatedialog.h"

#include <QMessageBox>

ValidateDialog::ValidateDialog(QWidget *parent) :
	QDialog(parent),
	ui_(new Ui::ValidateDialog),
	authResponse_(new AuthResponse(parent)),
	authkit_(authResponse_)
{
	ui_->setupUi(this);
	this->setMinimumHeight(150);
	this->setMinimumWidth(260);
	this->setMaximumHeight(270);
	this->setMaximumWidth(460);
	ui_->password_le->setEchoMode(QLineEdit::Password);
	on_online_rb_clicked();
}

ValidateDialog::~ValidateDialog()
{
	delete ui_;
}

void ValidateDialog::on_buttonBox_accepted()
{
	if(ui_->playername_le->text().isEmpty()){
		QMessageBox::warning(this, "Warning", "The playername cannot be empty.");
		exec();
	} else {
		accept();
		emit resultAccount(Account(ui_->online_rb->isChecked()?Mode::Online:Mode::Offline,
								   ui_->email_le->text(),
								   uuid_,
								   accessToken_,
								   clientToken_,
								   ui_->playername_le->text()));
	}
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

void ValidateDialog::on_login_pb_clicked()
{
	QByteArray data = AuthKit::kAuthenticateStyle.arg(ui_->email_le->text(),
													  ui_->password_le->text()).toUtf8();

	ui_->login_pb->setEnabled(false);
	connect(authResponse_, SIGNAL(authError(QString,QString)), this, SLOT(authError(QString,QString)));
	connect(authResponse_, SIGNAL(uuidUpdate(QString)), this, SLOT(uuidUpdate(QString)));
	connect(authResponse_, SIGNAL(accessTokenUpdate(QString)), this, SLOT(accessTokenUpdate(QString)));
	connect(authResponse_, SIGNAL(clientTokenUpdate(QString)), this, SLOT(clientTokenUpdate(QString)));
	connect(authResponse_, SIGNAL(playerNameUpdate(QString)), this, SLOT(playerNameUpdate(QString)));
	connect(authResponse_, SIGNAL(authenticateFinished(bool)), this, SLOT(authenticateFinished(bool)));
	authkit_.authenticate(data);
	disconnect(authResponse_, SIGNAL(authError(QString,QString)), this, SLOT(authError(QString,QString)));
	disconnect(authResponse_, SIGNAL(uuidUpdate(QString)), this, SLOT(uuidUpdate(QString)));
	disconnect(authResponse_, SIGNAL(accessTokenUpdate(QString)), this, SLOT(accessTokenUpdate(QString)));
	disconnect(authResponse_, SIGNAL(clientTokenUpdate(QString)), this, SLOT(clientTokenUpdate(QString)));
	disconnect(authResponse_, SIGNAL(playerNameUpdate(QString)), this, SLOT(playerNameUpdate(QString)));
	disconnect(authResponse_, SIGNAL(authenticateFinished(bool)), this, SLOT(authenticateFinished(bool)));

	ui_->login_pb->setEnabled(true);
	if(success_){
		ui_->email_le->setEnabled(false);
		ui_->password_label->setVisible(false);
		ui_->password_le->setVisible(false);
		ui_->showPassword_pb->setVisible(false);
		ui_->login_pb->setText("&Log out");
	} else{
//		QMessageBox::warning(this, "Error", "");
	}
}

void ValidateDialog::on_online_rb_clicked()
{
	ui_->playername_le->setEnabled(false);
	ui_->email_label->setVisible(true);
	ui_->email_le->setVisible(true);
	ui_->password_label->setVisible(true);
	ui_->password_le->setVisible(true);
	ui_->showPassword_pb->setVisible(true);
}

void ValidateDialog::on_offline_rb_clicked()
{
	ui_->playername_le->setEnabled(true);
	ui_->email_label->setVisible(false);
	ui_->email_le->setVisible(false);
	ui_->password_label->setVisible(false);
	ui_->password_le->setVisible(false);
	ui_->showPassword_pb->setVisible(false);
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

void ValidateDialog::authenticateFinished(bool ok)
{
	success_ = ok;
}

void ValidateDialog::authError(QString error, QString errorMessage)
{
	QMessageBox::warning(this, error, errorMessage);
}
