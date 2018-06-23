#include "validatedialog.h"
#include "ui_validatedialog.h"

#include "LAminec/Validator.h"

ValidateDialog::ValidateDialog(QWidget *parent, Validator *auth) :
	QDialog(parent),
	ui_(new Ui::ValidateDialog),
	activeAuth_(auth)
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
	if(activeAuth_->authenticate(ui_->email_le->text(),
						  ui_->password_le->text())){
		custom_.setEmail(ui_->email_le->text());
		custom_.setLogged(true);
		emit login(custom_.getEmail());
		this->accept();
	}
	else
		this->exec();
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

Account ValidateDialog::authenticate(const QString &email, const QString &password) const
{
	QByteArray data = AuthKit::kAuthenticateStyle.arg(email).arg(password).toUtf8();

	return authKit_.authenticate(data);
}
