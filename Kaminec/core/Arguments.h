#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <QList>
#include <QString>

class Arguments
{
public:
	Arguments() = default;
	Arguments(QString arguments);

	void replace(const QString& before, const QString& after);

	bool setOption(const QString& optionName, const QString& optionContent);

	void addOption(const QString& optionName);
	void addOption(const QString& optionName, const QString& optionContent);

	QStringList toStringList() const;

private:
	QList<QStringList> options;
};

#endif // ARGUMENTS_H
