#include "CheckInfo.h"

CheckInfo::CheckInfo(const QString &fileName,
					 const int &size,
					 const QCryptographicHash::Algorithm &checkCodeType,
					 const QString &checkCode,
					 const QString &path,
					 const QUrl &url) :
	fileName_(fileName),
	size_(size),
	checkCodeType_(checkCodeType),
	checkCode_(checkCode),
	path_(path),
	url_(url)
{}
