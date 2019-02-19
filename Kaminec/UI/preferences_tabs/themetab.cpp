#include "themetab.h"
#include "ui_themetab.h"

#include <QFontDialog>

#include "assistance/Custom.h"

ThemeTab::ThemeTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::ThemeTab)
{
	ui_->setupUi(this);
	ui_->font_le->setText(qApp->font().family());
}

ThemeTab::~ThemeTab()
{
	delete ui_;
}

void ThemeTab::on_font_pb_clicked()
{
	bool ok;
	auto font = QFontDialog::getFont(&ok, qApp->font(), this, tr("Choose font for Launcher..."));
	qApp->setFont(font);
	ui_->font_le->setText(font.family());
	Custom().setFont(font.toString());
}
