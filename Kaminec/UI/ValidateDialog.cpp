#include "validatedialog.h"
#include "ui_validatedialog.h"
#include "LAminec/ActiveAuth.h"

#include <QSettings>

ValidateDialog::ValidateDialog(QWidget *parent, ActiveAuth *auth) :
	QDialog(parent),
	ui(new Ui::ValidateDialog),
	activeAuth(auth)
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
	if(activeAuth->authenticate(ui->email_le->text(),
						  ui->password_le->text())){
		QSettings().setValue("email", ui->email_le->text());
		QSettings().setValue("isLogged", true);
		emit login(QSettings().value("id").toString());
		this->accept();
	}
	else
		this->exec();
}
