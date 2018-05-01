#include "Exception.h"

Exception::Exception(QString title, QString message) :
	exception(),
	title_(title),
	message_(message)
{}

const char *Exception::what() const noexcept
{
	return message_.toLatin1().constData();

}
