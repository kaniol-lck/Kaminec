#include "Deficiency.h"

Deficiency::Deficiency(bool ok) :
	ok_(ok)
{}

Deficiency::Deficiency(const QString &fileName, const QString &path, Type type, const QUrl url) :
	fileName_(fileName),
	path_(path),
	type_(type),
	url_(url)
{}

Deficiency::Deficiency(const CheckInfo &checkInfo, Type type) :
	fileName_(checkInfo.fileName_),
	path_(checkInfo.path_),
	type_(type),
	url_(checkInfo.url_)
{}
