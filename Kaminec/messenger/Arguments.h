#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <QList>

class Arguments
{
public:
	Arguments() = default;
	Arguments(const QString &arguments);
	Arguments(const QStringList &arguments);
	Arguments(const QVariant &arguments);

	void replace(const QString &before, const QString& after);

	bool setOption(const QString &optionName, const QString& optionContent);

	void addOption(const QString &optionName);
	void addOption(const QString &optionName, const QString& optionContent);

	QStringList toStringList() const;

private:
	QStringList arguments_;
	QList<int> optionGroupMark_;
};

#endif // ARGUMENTS_H
