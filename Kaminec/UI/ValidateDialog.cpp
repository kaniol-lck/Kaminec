#include "validatedialog.h"
#include "ui_validatedialog.h"

ValidateDialog::ValidateDialog(QWidget *parent, const QString &email) :
	QDialog(parent),
	ui_(new Ui::ValidateDialog)
{
	ui_->setupUi(this);
	this->setMinimumHeight(150);
	this->setMinimumWidth(260);
	this->setMaximumHeight(270);
	this->setMaximumWidth(460);
	ui_->password_le->setEchoMode(QLineEdit::Password);

	ui_->email_le->setText(email);
}

ValidateDialog::~ValidateDialog()
{
	delete ui_;
}

void ValidateDialog::on_buttonBox_accepted()
{
	emit login(ui_->email_le->text(),
			   ui_->password_le->text());
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
