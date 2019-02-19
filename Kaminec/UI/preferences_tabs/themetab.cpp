#include "themetab.h"
#include "ui_themetab.h"

#include "assistance/languages.hpp"

#include <QFontDialog>
#include <QTranslator>

ThemeTab::ThemeTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::ThemeTab)
{
	ui_->setupUi(this);
	ui_->fontComboBox->setCurrentFont(qApp->font());

	auto index = languages.indexOf(custom_.getLanguage());
	for(auto l : languages_display)
		ui_->lang_cb->addItem(l);
	ui_->lang_cb->setCurrentIndex(index);
}

void ThemeTab::accepted()
{
	auto lang = languages.at(ui_->lang_cb->currentIndex());
	if(lang != custom_.getLanguage()){
		custom_.setLanguage(lang);
		auto translator = new QTranslator();
		if(lang == "en_US"){
			qApp->removeTranslator(translator);
			return;
		}
		if(!translator->load(QCoreApplication::applicationDirPath()+"/languages/"+lang+".qm"))
			return;
		qApp->installTranslator(translator);
	}

	auto font = ui_->fontComboBox->currentFont();
	qApp->setFont(font);
	custom_.setFont(font.toString());
}

ThemeTab::~ThemeTab()
{
	delete ui_;
}

void ThemeTab::on_font_pb_clicked()
{
	bool ok;
	auto font = QFontDialog::getFont(&ok, qApp->font(), this, tr("Choose font for Launcher..."));
	if(ok)
		ui_->fontComboBox->setCurrentFont(font);
}
