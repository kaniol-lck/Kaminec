#include "preference.h"
#include "ui_preference.h"

#include "core/Path.h"
#include "UI/ValidateDialog.h"

#include <QProcess>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

Preference::Preference(QWidget *parent, ActiveAuth *auth) :
	QDialog(parent),
	ui_(new Ui::Preference),
	activeAuth_(auth)
{
	setWindowFlags(Qt::Dialog);
	ui_->setupUi(this);

	ui_->versionsPath_label->setVisible(false);
	ui_->versionsPath_le->setVisible(false);
	ui_->versionsPath_showPb->setVisible(false);
	ui_->libsPath_label->setVisible(false);
	ui_->libsPath_le->setVisible(false);
	ui_->libsPath_showPb->setVisible(false);
	ui_->nativesPath_label->setVisible(false);
	ui_->nativesPath_le->setVisible(false);
	ui_->nativesPath_showPb->setVisible(false);
	ui_->assetsPath_label->setVisible(false);
	ui_->assetsPath_le->setVisible(false);
	ui_->assetsPath_showPb->setVisible(false);
	ui_->indexesPath_label->setVisible(false);
	ui_->indexesPath_le->setVisible(false);
	ui_->indexesPath_showPb->setVisible(false);
	ui_->objectsPath_label->setVisible(false);
	ui_->objectsPath_le->setVisible(false);
	ui_->objectsPath_showPb->setVisible(false);
	ui_->customPathHelper_tb->setVisible(false);


	QSettings settings;
	//load exsit preference
	ui_->playerName_le->setText(settings.value("playerName", "Steve").toString());
	ui_->autoName_cb->setChecked(settings.value("autoName", false).toBool());

	ui_->corePath_le->setText(Path::corePath());
	ui_->versionsPath_le->setText(settings.value("path/versionsPath", "<core>/versions").toString());
	ui_->libsPath_le->setText(settings.value("path/libsPath", "<core>/libraries").toString());
	ui_->nativesPath_le->setText(settings.value("path/nativesPath", "<core>/natives").toString());
	ui_->assetsPath_le->setText(settings.value("path/assetsPath", "<core>/assets").toString());
	ui_->indexesPath_le->setText(settings.value("path/indexesPath", "<assets>/indexes").toString());
	ui_->objectsPath_le->setText(settings.value("path/objectsPath", "<assets>/objects").toString());

	ui_->fullScreen_checkBox->setChecked(settings.value("fullScreen", false).toBool());
	ui_->width_sb->setValue(settings.value("width", 854).toInt());
	ui_->height_sb->setValue(settings.value("height", 480).toInt());

	ui_->javaPath_le->setText(settings.value("javaPath", "").toString());
	ui_->minMem_sb->setValue(settings.value("minMem", 1024).toInt());
	ui_->maxMem_sb->setValue(settings.value("maxMem", 1024).toInt());
	ui_->javaArg_te->setText(settings.value("javaArg", "").toString().replace("\\n","\n"));

	//check if you logged in
	if(settings.value("isLogged", false).toBool()){
		ui_->logName_label->setText("Logon account:" + settings.value("email", "").toString());
		ui_->login_pb->setText("&Log out");
	}

	//check if you point out javaPath
	if(ui_->javaPath_le->text() == "")
		ui_->javaPath_le->setText(getAutoJavaPath());
}

Preference::~Preference()
{
	delete ui_;
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
													  ui_->corePath_le->text());
	if(corePath!=""){
		if(corePath.endsWith("/.minecraft"))
			ui_->corePath_le->setText(corePath);
		else
			ui_->corePath_le->setText(corePath + "/.minecraft");
	}
}

void Preference::on_javaPath_showPb_clicked()
{
	auto javaPath = QFileDialog::getOpenFileName(this,
												 "Choose javaw,exe...",
												 "C:/","javaw(javaw.exe)");
	if(javaPath!="")
		ui_->javaPath_le->setText(javaPath);
}

void Preference::on_buttonBox_accepted()
{
	settings_.setValue("playerName", ui_->playerName_le->text());
	settings_.setValue("autoName", ui_->autoName_cb->isChecked());

	settings_.setValue("path/corePath", ui_->corePath_le->text());
	settings_.setValue("path/versionsPath", ui_->versionsPath_le->text());
	settings_.setValue("path/libsPath", ui_->libsPath_le->text());
	settings_.setValue("path/nativesPath", ui_->nativesPath_le->text());
	settings_.setValue("path/assetsPath", ui_->assetsPath_le->text());
	settings_.setValue("path/indexesPath", ui_->indexesPath_le->text());
	settings_.setValue("path/objectsPath", ui_->objectsPath_le->text());

	settings_.setValue("fullScreen", ui_->fullScreen_checkBox->isChecked());
	settings_.setValue("width", ui_->width_sb->value());
	settings_.setValue("height", ui_->height_sb->value());

	settings_.setValue("javaPath", ui_->javaPath_le->text());
	settings_.setValue("minMem", ui_->minMem_sb->value());
	settings_.setValue("maxMem", ui_->maxMem_sb->value());
	settings_.setValue("javaArg", ui_->javaArg_te->toPlainText().replace("\n","\\n"));

	emit settingfinished();
}

void Preference::on_login_pb_clicked()
{
	if(settings_.value("isLogged", false).toBool()){
		activeAuth_->invalidate();

		settings_.setValue("isLogged", false);
		ui_->logName_label->setText("You have not logged in.");
		ui_->login_pb->setText("&Log in");
	}else {
		auto validateDialog = new ValidateDialog(this, activeAuth_);

		connect(validateDialog, SIGNAL(login(QString)), this, SLOT(logChanged(QString)));

		validateDialog->show();
	}
}

void Preference::logChanged(QString email)
{
	ui_->logName_label->setText("Logon account:" + email);
	ui_->login_pb->setText("&Log out");
}

void Preference::on_autoName_cb_stateChanged(int arg1)
{
	if(arg1 == Qt::Checked){
		ui_->playerName_le->setText(settings_.value("id").toString());
		ui_->playerName_le->setEnabled(false);
	} else /*arg1 == Qt::Unchecked*/{
		ui_->playerName_le->setText(settings_.value("playerName").toString());
		ui_->playerName_le->setEnabled(true);
	}
}

void Preference::on_fullScreen_checkBox_stateChanged(int arg1)
{
	if(arg1 == Qt::Checked){
		ui_->width_sb->setEnabled(false);
		ui_->height_sb->setEnabled(false);
	} else /*arg1 == Qt::Unchecked*/{
		ui_->width_sb->setEnabled(true);
		ui_->height_sb->setEnabled(true);
	}
}

void Preference::on_more_pb_clicked()
{
	customPath_ = !customPath_;

	ui_->versionsPath_label->setVisible(customPath_);
	ui_->versionsPath_le->setVisible(customPath_);
	ui_->versionsPath_showPb->setVisible(customPath_);
	ui_->libsPath_label->setVisible(customPath_);
	ui_->libsPath_le->setVisible(customPath_);
	ui_->libsPath_showPb->setVisible(customPath_);
	ui_->nativesPath_label->setVisible(customPath_);
	ui_->nativesPath_le->setVisible(customPath_);
	ui_->nativesPath_showPb->setVisible(customPath_);
	ui_->assetsPath_label->setVisible(customPath_);
	ui_->assetsPath_le->setVisible(customPath_);
	ui_->assetsPath_showPb->setVisible(customPath_);
	ui_->indexesPath_label->setVisible(customPath_);
	ui_->indexesPath_le->setVisible(customPath_);
	ui_->indexesPath_showPb->setVisible(customPath_);
	ui_->objectsPath_label->setVisible(customPath_);
	ui_->objectsPath_le->setVisible(customPath_);
	ui_->objectsPath_showPb->setVisible(customPath_);
	ui_->customPathHelper_tb->setVisible(customPath_);

	ui_->more_pb->setText(customPath_?"Fold":"More");
}
