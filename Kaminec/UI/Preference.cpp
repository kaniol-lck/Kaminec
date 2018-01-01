#include "preference.h"
#include "core/Path.h"
#include "ui_preference.h"
#include "UI/ValidateDialog.h"
#include "LAminec/ActiveAuth.h"

#include <QStringList>
#include <QProcess>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDebug>

Preference::Preference(QWidget *parent, ActiveAuth *auth) :
	QDialog(parent),
	ui(new Ui::Preference),
	activeAuth(auth)
{
	setWindowFlags(Qt::Dialog);
	ui->setupUi(this);

	ui->versionsPath_label->setVisible(false);
	ui->versionsPath_le->setVisible(false);
	ui->versionsPath_showPb->setVisible(false);
	ui->libsPath_label->setVisible(false);
	ui->libsPath_le->setVisible(false);
	ui->libsPath_showPb->setVisible(false);
	ui->nativesPath_label->setVisible(false);
	ui->nativesPath_le->setVisible(false);
	ui->nativesPath_showPb->setVisible(false);
	ui->assetsPath_label->setVisible(false);
	ui->assetsPath_le->setVisible(false);
	ui->assetsPath_showPb->setVisible(false);
	ui->indexesPath_label->setVisible(false);
	ui->indexesPath_le->setVisible(false);
	ui->indexesPath_showPb->setVisible(false);
	ui->objectsPath_label->setVisible(false);
	ui->objectsPath_le->setVisible(false);
	ui->objectsPath_showPb->setVisible(false);
	ui->customPathHelper_tb->setVisible(false);


	QSettings settings;
	//load exsit preference
	ui->playerName_le->setText(settings.value("playerName", "Steve").toString());
	ui->autoName_cb->setChecked(settings.value("autoName", false).toBool());

	ui->corePath_le->setText(Path::corePath());
	ui->versionsPath_le->setText(settings.value("path/versionsPath", "<core>/versions").toString());
	ui->libsPath_le->setText(settings.value("path/libsPath", "<core>/libraries").toString());
	ui->nativesPath_le->setText(settings.value("path/nativesPath", "<core>/natives").toString());
	ui->assetsPath_le->setText(settings.value("path/assetsPath", "<core>/assets").toString());
	ui->indexesPath_le->setText(settings.value("path/indexesPath", "<assets>/indexes").toString());
	ui->objectsPath_le->setText(settings.value("path/objectsPath", "<assets>/objects").toString());

	ui->fullScreen_checkBox->setChecked(settings.value("fullScreen", false).toBool());
	ui->width_sb->setValue(settings.value("width", 854).toInt());
	ui->height_sb->setValue(settings.value("height", 480).toInt());

	ui->javaPath_le->setText(settings.value("javaPath", "").toString());
	ui->minMem_sb->setValue(settings.value("minMem", 1024).toInt());
	ui->maxMem_sb->setValue(settings.value("maxMem", 1024).toInt());
	ui->javaArg_te->setText(settings.value("javaArg", "").toString().replace("\\n","\n"));

	//check if you logged in
	if(settings.value("isLogged", false).toBool()){
		ui->logName_label->setText("Logon account:" + settings.value("email", "").toString());
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
	auto PATH = environment.at(environment.indexOf(QRegExp("PATH=.*"))).split(";");
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
	settings.setValue("playerName", ui->playerName_le->text());
	settings.setValue("autoName", ui->autoName_cb->isChecked());

	settings.setValue("path/corePath", ui->corePath_le->text());
	settings.setValue("path/versionsPath", ui->versionsPath_le->text());
	settings.setValue("path/libsPath", ui->libsPath_le->text());
	settings.setValue("path/nativesPath", ui->nativesPath_le->text());
	settings.setValue("path/assetsPath", ui->assetsPath_le->text());
	settings.setValue("path/indexesPath", ui->indexesPath_le->text());
	settings.setValue("path/objectsPath", ui->objectsPath_le->text());

	settings.setValue("fullScreen", ui->fullScreen_checkBox->isChecked());
	settings.setValue("width", ui->width_sb->value());
	settings.setValue("height", ui->height_sb->value());

	settings.setValue("javaPath", ui->javaPath_le->text());
	settings.setValue("minMem", ui->minMem_sb->value());
	settings.setValue("maxMem", ui->maxMem_sb->value());
	settings.setValue("javaArg", ui->javaArg_te->toPlainText().replace("\n","\\n"));
}

void Preference::on_login_pb_clicked()
{
	if(settings.value("isLogged", false).toBool()){
		activeAuth->invalidate();

		settings.setValue("isLogged", false);
		ui->logName_label->setText("You have not logged in.");
		ui->login_pb->setText("&Log in");
	}else {
		auto validateDialog = new ValidateDialog(this, activeAuth);

		connect(validateDialog, SIGNAL(login(QString)), this, SLOT(logChanged(QString)));

		validateDialog->show();
	}
}

void Preference::logChanged(QString email)
{
	ui->logName_label->setText("Logon account:" + email);
	ui->login_pb->setText("&Log out");
}

void Preference::on_autoName_cb_stateChanged(int arg1)
{
	if(arg1 == Qt::Checked){
		ui->playerName_le->setText(settings.value("id").toString());
		ui->playerName_le->setEnabled(false);
	} else /*arg1 == Qt::Unchecked*/{
		ui->playerName_le->setText(settings.value("playerName").toString());
		ui->playerName_le->setEnabled(true);
	}
}

void Preference::on_fullScreen_checkBox_stateChanged(int arg1)
{
	if(arg1 == Qt::Checked){
		ui->width_sb->setEnabled(false);
		ui->height_sb->setEnabled(false);
	} else /*arg1 == Qt::Unchecked*/{
		ui->width_sb->setEnabled(true);
		ui->height_sb->setEnabled(true);
	}
}

void Preference::on_more_pb_clicked()
{
	customPath = !customPath;

	ui->versionsPath_label->setVisible(customPath);
	ui->versionsPath_le->setVisible(customPath);
	ui->versionsPath_showPb->setVisible(customPath);
	ui->libsPath_label->setVisible(customPath);
	ui->libsPath_le->setVisible(customPath);
	ui->libsPath_showPb->setVisible(customPath);
	ui->nativesPath_label->setVisible(customPath);
	ui->nativesPath_le->setVisible(customPath);
	ui->nativesPath_showPb->setVisible(customPath);
	ui->assetsPath_label->setVisible(customPath);
	ui->assetsPath_le->setVisible(customPath);
	ui->assetsPath_showPb->setVisible(customPath);
	ui->indexesPath_label->setVisible(customPath);
	ui->indexesPath_le->setVisible(customPath);
	ui->indexesPath_showPb->setVisible(customPath);
	ui->objectsPath_label->setVisible(customPath);
	ui->objectsPath_le->setVisible(customPath);
	ui->objectsPath_showPb->setVisible(customPath);
	ui->customPathHelper_tb->setVisible(customPath);

	ui->more_pb->setText(customPath?"Fold":"More");
}
