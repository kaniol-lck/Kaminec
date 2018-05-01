#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <QString>

class Exception : public std::exception
{
public:
	Exception(QString title, QString message);
	virtual const char *what() const noexcept;

	virtual ~Exception() noexcept = default;

private:
	QString title_;
	QString message_;

};

#endif // EXCEPTION_H
