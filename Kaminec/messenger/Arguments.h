#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <QList>
#include <QStringList>
#include <memory>

class Arguments
{
public:
	Arguments() = default;
	Arguments(const QString &arguments);
	Arguments(const QStringList &arguments);

	void replace(const QString &before, const QString& after);

	void setOption(const QString &optionName, const QString& optionContent);
	void setOption(const QString &optionName);

	void append(Arguments arguments);

	QStringList toStringList() const;
	QString toString() const;

	static Arguments fromVariant(const QVariant &arguments);

private:
	QList<QStringList> arguments_;
};

#endif // ARGUMENTS_H
