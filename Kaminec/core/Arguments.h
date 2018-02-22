#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <QList>

class Arguments
{
public:
	Arguments() = default;
	Arguments(const QString &arguments);

	void replace(const QString &before, const QString& after);

	bool setOption(const QString &optionName, const QString& optionContent);

	void addOption(const QString &optionName);
	void addOption(const QString &optionName, const QString& optionContent);

	QStringList toStringList() const;

private:
	QList<QStringList> options_;
};

#endif // ARGUMENTS_H
