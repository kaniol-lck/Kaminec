#include "profile.h"

Profile::Profile(const QString &name,
				 const QString &lastVersionId,
				 const QString &gameDir):
	name_(name),
	lastVersionId_(lastVersionId),
	gameDir_(gameDir)
{}
