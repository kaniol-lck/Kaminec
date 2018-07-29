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
}

ValidateDialog::~ValidateDialog()
{
	delete ui_;
}

void ValidateDialog::on_buttonBox_accepted()
{
	emit resultAccount(Account(ui_->online_rb->isChecked()?Mode::Online:Mode::Offline,
							   ui_->email_le->text(),
							   uuid_,
							   accessToken_,
							   clientToken_,
							   playername_));
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
	QByteArray data = AuthKit::kTokenStyle.arg(ui_->email_le->text(),
											   ui_->password_le->text()).toUtf8();
	connect(authResponse_, SIGNAL(authenticateFinished(bool)), this, SLOT(authenticateFinished(bool)));
	authkit_.validate(data);
	disconnect(authResponse_, SIGNAL(authenticateFinished(bool)), this, SLOT(authenticateFinished(bool)));

	if(success_){
		ui_->email_le->setEnabled(false);
		ui_->password_label->setVisible(false);
		ui_->password_le->setVisible(false);
		ui_->showPassword_pb->setVisible(false);
		ui_->login_pb->setText("&Log out");
	} else{
		QMessageBox::warning(this, "Error", "");
	}

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
	playername_ = playername;
}

void ValidateDialog::authenticateFinished(bool ok)
{
	success_ = ok;
}
