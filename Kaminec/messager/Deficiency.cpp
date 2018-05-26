#include "Deficiency.h"

Deficiency::Deficiency(bool ok) :
	ok_(ok)
{}

Deficiency::Deficiency(const QString &fileName, const QString &path, Type type) :
	fileName_(fileName),
	path_(path),
	type_(type)
{}

Deficiency::Deficiency(const CheckInfo &checkInfo, Type type) :
	fileName_(checkInfo.fileName_),
	path_(checkInfo.path_),
	type_(type)
{}
