#include "validatedialog.h"
#include "ui_validatedialog.h"
#include "auth.h"

#include <QSettings>

ValidateDialog::ValidateDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ValidateDialog)
{
	ui->setupUi(this);

	this->setMinimumHeight(150);
	this->setMinimumWidth(260);
	this->setMaximumHeight(270);
	this->setMaximumWidth(460);

	ui->password_le->setEchoMode(QLineEdit::Password);

}

ValidateDialog::~ValidateDialog()
{
	delete ui;
}

void ValidateDialog::on_showPassword_pb_clicked()
{

	if(showPassword){
		showPassword = false;
		ui->password_le->setEchoMode(QLineEdit::Password);
		ui->showPassword_pb->setText("&Show Password");
	}else{
		showPassword = true;
		ui->password_le->setEchoMode(QLineEdit::Normal);
		ui->showPassword_pb->setText("&Hide Password");
	}
}

void ValidateDialog::on_buttonBox_accepted()
{
	auto auth = new Auth(this, qMakePair(ui->email_le->text(),
									 ui->password_le->text()));

	if(auth->check()){
		QSettings().setValue("email", ui->email_le->text());
		QSettings().setValue("isLogged",true);
		emit login(ui->email_le->text());
		this->accept();
	}
	else
		this->exec();
}
