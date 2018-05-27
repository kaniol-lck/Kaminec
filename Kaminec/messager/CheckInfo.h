#ifndef CHECKINFO_H
#define CHECKINFO_H

#include <QCryptographicHash>
#include <QString>
#include <QUrl>

struct CheckInfo
{
public:

	CheckInfo() = default;
	explicit CheckInfo(const QString &fileName,
					   const int &size,
					   const QCryptographicHash::Algorithm &checkCodeType,
					   const QString &checkCode,
					   const QString &path,
					   const QUrl &url);

	QString fileName_;
	int size_;
	QCryptographicHash::Algorithm checkCodeType_;
	QString checkCode_;
	QString path_;
	QUrl url_;
};

#endif // CHECKINFO_H
