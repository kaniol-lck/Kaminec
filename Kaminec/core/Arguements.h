#ifndef ARGUEMENTS_H
#define ARGUEMENTS_H

#include <QList>
#include <QString>

class Arguements
{
public:
	Arguements() = default;
	Arguements(QString arguements);

	void replace(const QString& before, const QString& after);

	bool setOption(const QString& optionName, const QString& optionContent);

	void addOption(const QString& optionName);
	void addOption(const QString& optionName, const QString& optionContent);

	QStringList toStringList() const;

private:
	QList<QStringList> options;
};

#endif // ARGUEMENTS_H
