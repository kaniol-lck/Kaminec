#ifndef LANGUAGES_HPP
#define LANGUAGES_HPP

#include <QLocale>
#include <QStringList>
#include <QList>

const QStringList languages = {
	"en_US",
	"zh_CN"
};

const QStringList languages_display = {
	"English-American",
	"简体中文"
};

const QList<QLocale::Country> languages_code = {
	QLocale::UnitedStates,
	QLocale::China
};

#endif // LANGUAGES_HPP
