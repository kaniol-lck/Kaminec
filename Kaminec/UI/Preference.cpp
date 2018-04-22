#include "preference.h"
#include "ui_preference.h"

#include "assistance/Path.h"
#include "UI/ValidateDialog.h"

#include <QProcess>
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

	//load exsit preference

	ui_->playerName_le->setText(custom_.getPlayerName());
	ui_->autoName_cb->setChecked(custom_.getAutoOfficialName());

	ui_->corePath_le->setText(custom_.getCoreGameFileDirectory());
	ui_->versionsPath_le->setText(custom_.getGameVersionsDirectory());
	ui_->libsPath_le->setText(custom_.getGameLibrariesDirectory());
	ui_->nativesPath_le->setText(custom_.getGameNativesDirectory());
	ui_->assetsPath_le->setText(custom_.getAssetsDirectory());
	ui_->indexesPath_le->setText(custom_.getAssetsIndexesDirectory());
	ui_->objectsPath_le->setText(custom_.getAssetsObjectsDirectory());
	ui_->unusedModsPath_le->setText(custom_.getUnusedModsDirectory());
	ui_->savesBackupPath_le->setText(custom_.getSavesBackupDirectory());
	ui_->loggerPath_le->setText(custom_.getLoggerDirectory());
	ui_->javaPath_le_2->setText(custom_.getJavaDirectory());

	ui_->fullScreen_checkBox->setChecked(custom_.getGameWindowFullScreen());
	auto size = custom_.getGameWindowSize();
	ui_->width_sb->setValue(size.first);
	ui_->height_sb->setValue(size.second);

	ui_->javaPath_le->setText(custom_.getJavaDirectory());
	auto range = custom_.getMemoryAllocateRange();
	ui_->minMem_sb->setValue(range.first);
	ui_->maxMem_sb->setValue(range.second);

	//check if you logged in
	if(custom_.getLogged()){
		ui_->logName_label->setText("Logon account:" + custom_.getEmail());
		ui_->login_pb->setText("&Log out");
	}

//	//check if you point out javaPath
//	if(ui_->javaPath_le->text() == "")
//		ui_->javaPath_le->setText(getAutoJavaPath());
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
	custom_.setPlayerName(ui_->playerName_le->text());
	custom_.setAutoOfficialName(ui_->autoName_cb->isChecked());

	custom_.setCoreGameFileDirectory(ui_->corePath_le->text());
	custom_.setGameVersionsDirectory(ui_->versionsPath_le->text());
	custom_.setGameLibrariesDirectory(ui_->libsPath_le->text());
	custom_.setGameNativesDirectory(ui_->nativesPath_le->text());
	custom_.setAssetsDirectory(ui_->assetsPath_le->text());
	custom_.setAssetsIndexesDirectory(ui_->indexesPath_le->text());
	custom_.setAssetsObjectsDirectory(ui_->objectsPath_le->text());
	custom_.setUnusedModsDirectory(ui_->unusedModsPath_le->text());
	custom_.setSavesBackupDirectory(ui_->savesBackupPath_le->text());
	custom_.setLoggerDirectory(ui_->loggerPath_le->text());

	custom_.setGameWindowFullScreen(ui_->fullScreen_checkBox->isChecked());
	custom_.setGameWindowSize(ui_->width_sb->value(),
							  ui_->height_sb->value());

	custom_.setJavaDirectory(ui_->javaPath_le->text());
	custom_.setMemoryAllocateRange(ui_->minMem_sb->value(),
								   ui_->maxMem_sb->value());

	emit settingfinished();
}

void Preference::on_login_pb_clicked()
{
	if(custom_.getLogged()){
		activeAuth_->invalidate();

		custom_.setLogged(false);
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
		ui_->playerName_le->setText(custom_.getOfficialName());
		ui_->playerName_le->setEnabled(false);
	} else /*arg1 == Qt::Unchecked*/{
		ui_->playerName_le->setText(custom_.getPlayerName());
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

void Preference::on_more_pb_toggled(bool checked)
{
	ui_->versionsPath_label->setVisible(checked);
	ui_->versionsPath_le->setVisible(checked);
	ui_->versionsPath_showPb->setVisible(checked);
	ui_->libsPath_label->setVisible(checked);
	ui_->libsPath_le->setVisible(checked);
	ui_->libsPath_showPb->setVisible(checked);
	ui_->nativesPath_label->setVisible(checked);
	ui_->nativesPath_le->setVisible(checked);
	ui_->nativesPath_showPb->setVisible(checked);
	ui_->assetsPath_label->setVisible(checked);
	ui_->assetsPath_le->setVisible(checked);
	ui_->assetsPath_showPb->setVisible(checked);
	ui_->indexesPath_label->setVisible(checked);
	ui_->indexesPath_le->setVisible(checked);
	ui_->indexesPath_showPb->setVisible(checked);
	ui_->objectsPath_label->setVisible(checked);
	ui_->objectsPath_le->setVisible(checked);
	ui_->objectsPath_showPb->setVisible(checked);
	ui_->customPathHelper_tb->setVisible(checked);

	ui_->more_pb->setText(checked?"Fold":"More");
}

void Preference::on_javaPath_le_2_textEdited(const QString &arg1)
{
	ui_->javaPath_le->setText(arg1);
}

void Preference::on_javaPath_le_textEdited(const QString &arg1)
{
	ui_->javaPath_le_2->setText(arg1);
}

void Preference::on_javaPath_showPb_2_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the version directory",
													  ui_->versionsPath_le->text());

	if(path!="")
		ui_->versionsPath_le->setText(path);
}

void Preference::on_versionsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the version directory",
													  ui_->versionsPath_le->text());

	if(path!="")
		ui_->versionsPath_le->setText(path);
}

void Preference::on_libsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the libraries directory",
													  ui_->libsPath_le->text());

	if(path!="")
		ui_->libsPath_le->setText(path);
}

void Preference::on_nativesPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the natives directory",
													  ui_->nativesPath_le->text());

	if(path!="")
		ui_->nativesPath_le->setText(path);
}

void Preference::on_assetsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the assets directory",
													  ui_->assetsPath_le->text());

	if(path!="")
		ui_->assetsPath_le->setText(path);
}

void Preference::on_indexesPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the asset indexes directory",
													  ui_->indexesPath_le->text());

	if(path!="")
		ui_->indexesPath_le->setText(path);
}

void Preference::on_objectsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the asset objects directory",
													  ui_->objectsPath_le->text());

	if(path!="")
		ui_->objectsPath_le->setText(path);
}

void Preference::on_unusedModsPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the unused mods directory",
													  ui_->unusedModsPath_le->text());

	if(path!="")
		ui_->unusedModsPath_le->setText(path);
}

void Preference::on_savesBackupPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the saves backup directory",
													  ui_->savesBackupPath_le->text());

	if(path!="")
		ui_->savesBackupPath_le->setText(path);
}

void Preference::on_loggerPath_showPb_clicked()
{
	auto path = QFileDialog::getExistingDirectory(this, "Please choose the logger directory",
													  ui_->loggerPath_le->text());

	if(path!="")
		ui_->loggerPath_le->setText(path);
}
