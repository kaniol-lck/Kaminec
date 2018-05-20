#ifndef CHECKINFO_H
#define CHECKINFO_H

#include <QCryptographicHash>
#include <QString>

struct CheckInfo
{
public:

	CheckInfo() = default;
	explicit CheckInfo(const QString &fileName,
					   const int &size,
					   const QCryptographicHash::Algorithm &checkCodeType,
					   const QString &checkCode,
					   const QString &path);

	QString fileName_;
	int size_;
	QCryptographicHash::Algorithm checkCodeType_;
	QString checkCode_;
	QString path_;
};

#endif // CHECKINFO_H
