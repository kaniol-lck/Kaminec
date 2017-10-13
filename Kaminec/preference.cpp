#include "preference.h"
#include "ui_preference.h"
#include "validatedialog.h"
#include "auth.h"

#include <QStringList>
#include <QProcess>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDebug>

Preference::Preference(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Preference)
{
	setWindowFlags(Qt::Dialog);
	ui->setupUi(this);


	QSettings settings;
	//load exsit preference
	ui->playerName_le->setText(settings.value("playerName","Steve").toString());
	ui->autoName_cb->setChecked(settings.value("autoName",true).toBool());

	ui->corePath_le->setText(settings.value("corePath",
											QStandardPaths::writableLocation(
												QStandardPaths::AppDataLocation) + "/.minecraft").toString());
	ui->width_sb->setValue(settings.value("width",854).toInt());
	ui->height_sb->setValue(settings.value("height",480).toInt());

	ui->javaPath_le->setText(settings.value("javaPath","").toString());
	ui->minMem_sb->setValue(settings.value("minMem",1024).toInt());
	ui->maxMem_sb->setValue(settings.value("maxMem",1024).toInt());
	ui->javaArg_te->setText(settings.value("javaArg","").toString());

	//check if you logged in
	if(settings.value("isLogged",false).toBool()){
		ui->logName_label->setText("Logon account:" + settings.value("email","").toString());
		ui->login_pb->setText("&Log out");
	}

	//check if you point out javaPath
	if(ui->javaPath_le->text() == "")
		ui->javaPath_le->setText(getAutoJavaPath());
}

Preference::~Preference()
{
	delete ui;
}

QString Preference::getAutoJavaPath()
{
	auto environment = QProcess::systemEnvironment();
	auto PATH = environment.at(environment.indexOf(QRegExp("PATH=.*")))
						   .split(";");
	auto index = PATH.indexOf(QRegExp(".*\\javapath"));
	if(index==-1){
		return QString();
	}
	auto javaPath = PATH.at(index);
	javaPath.replace('\\',"/");
	javaPath.append("/javaw.exe");

	return javaPath;
}

void Preference::on_corePath_showPb_clicked()
{
	auto corePath = QFileDialog::getExistingDirectory(0, "Please choose the upper directory,we will automaticly create \".minecraft\" folder",
													  ui->corePath_le->text());
	if(corePath!=""){
		if(corePath.endsWith("/.minecraft"))
			ui->corePath_le->setText(corePath);
		else
			ui->corePath_le->setText(corePath + "/.minecraft");
	}
}

void Preference::on_javaPath_showPb_clicked()
{
	auto javaPath = QFileDialog::getOpenFileName(this,
												 "Choose javaw,exe...",
												 "C:/","javaw(javaw.exe)");
	if(javaPath!="")
		ui->javaPath_le->setText(javaPath);
}

void Preference::on_buttonBox_accepted()
{
	QSettings settings;

	settings.setValue("playerName",ui->playerName_le->text());
	settings.setValue("autoName",ui->autoName_cb->isChecked());

	settings.setValue("corePath",ui->corePath_le->text());
	settings.setValue("width",ui->width_sb->value());
	settings.setValue("height",ui->height_sb->value());

	settings.setValue("javaPath",ui->javaPath_le->text());
	settings.setValue("minMem",ui->minMem_sb->value());
	settings.setValue("maxMem",ui->maxMem_sb->value());
	settings.setValue("javaArg",ui->javaArg_te->toPlainText());

	settings.sync();
}

void Preference::on_login_pb_clicked()
{
	if(QSettings().value("isLogged",false).toBool()){
		auto auth = new Auth(this);
		auth->invalidate();

		ui->logName_label->setText("You have not logged in.");
		ui->login_pb->setText("&Log in");
	}else {
		auto validateDialog = new ValidateDialog(this);

		connect(validateDialog, SIGNAL(login(QString)), this, SLOT(logChanged(QString)));

		validateDialog->show();
	}
}

void Preference::logChanged(QString email)
{
	ui->logName_label->setText("Logon account:" + email);
	ui->login_pb->setText("&Log out");
}
