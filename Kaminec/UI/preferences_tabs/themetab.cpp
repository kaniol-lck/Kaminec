#include "themetab.h"
#include "ui_themetab.h"

#include <QFontDialog>

ThemeTab::ThemeTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::ThemeTab)
{
	ui_->setupUi(this);
	ui_->fontComboBox->setCurrentFont(qApp->font());

}

void ThemeTab::accepted()
{
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
