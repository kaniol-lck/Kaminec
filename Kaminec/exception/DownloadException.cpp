#include "DownloadException.h"

DownloadException::DownloadException(QString message) :
	Exception("Download Error occured.", message)
{}
