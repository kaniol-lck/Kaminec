#include "launchertab.h"
#include "ui_launchertab.h"

#include "assistance/languages.hpp"

#include <QTranslator>

LauncherTab::LauncherTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::LauncherTab)
{
	ui_->setupUi(this);
	ui_->logNumber_spinBox->setValue(custom_.getLogFileNumber());

	auto index = languages.indexOf(custom_.getLanguage());
	for(auto l : languages_display)
		ui_->lang_cb->addItem(l);
	ui_->lang_cb->setCurrentIndex(index);
}

void LauncherTab::accepted()
{
	custom_.setLogFileNumber(ui_->logNumber_spinBox->value());
}

LauncherTab::~LauncherTab()
{
	delete ui_;
}

void LauncherTab::on_logNumber_spinBox_valueChanged(int arg1)
{
	ui_->logTip_label->setVisible(arg1 == -1);
}

void LauncherTab::on_lang_cb_currentIndexChanged(const QString &)
{
	auto lang = languages.at(ui_->lang_cb->currentIndex());
	if(lang != custom_.getLanguage()){
		custom_.setLanguage(lang);
		auto translator = new QTranslator();
		if(!translator->load(QCoreApplication::applicationDirPath()+"/languages/"+lang+".qm"))
			return;
		qApp->installTranslator(translator);
	}
}
