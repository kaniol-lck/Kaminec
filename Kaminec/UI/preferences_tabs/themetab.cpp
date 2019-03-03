#include "themetab.h"
#include "ui_themetab.h"

#include <QFontDialog>
#include <QFileDialog>
#include <QDebug>

ThemeTab::ThemeTab(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::ThemeTab)
{
	ui_->setupUi(this);
	auto font = qApp->font();
	ui_->fontComboBox->setCurrentFont(font);
	ui_->font_spinBox->setValue(font.pointSize());
	ui_->background_le->setText(custom_.getBackground());
	connect(ui_->fontComboBox, &QFontComboBox::currentFontChanged, this, &ThemeTab::updateFont);
	connect(ui_->font_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ThemeTab::updateFont);
}

void ThemeTab::accepted()
{

}

ThemeTab::~ThemeTab()
{
	delete ui_;
}

void ThemeTab::on_font_pb_clicked()
{
	bool ok;
	auto font = QFontDialog::getFont(&ok, qApp->font(), this, tr("Choose font for Launcher..."));
	if(ok){
		ui_->fontComboBox->setCurrentFont(font);
		ui_->font_spinBox->setValue(font.pointSize());
	}
}

void ThemeTab::on_background_showPb_clicked()
{
	auto filename = QFileDialog::getOpenFileName(this, tr("Choose background for Launcher..."), ui_->background_le->text(), "Images(*.png *.jpg *.jpeg *.gif)");
	if(!filename.isEmpty()){
		custom_.setBackground(filename);
		ui_->background_le->setText(filename);
		emit updateBackground();
	}
}

void ThemeTab::updateFont()
{
	auto font = ui_->fontComboBox->currentFont();
	font.setPointSize(ui_->font_spinBox->value());
	qApp->setFont(font);
	custom_.setFont(font.toString());
}
