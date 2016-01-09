#ifndef ARANGO_EXCEPTION_H
#define ARANGO_EXCEPTION_H

#include <exception>
#include <string>

namespace arango {

class exception : public std::exception
{
	public:
		explicit exception(const char* message);
		explicit exception(const std::string &message);
		virtual ~exception();
		virtual const char* what() const noexcept;

	private:
		std::string m_message;
};

class unauthorized_exception : public exception
{
	public:
		unauthorized_exception();
};

class connection_exception : public exception
{
	public:
		using exception::exception;
};

} // namespace arango

#endif // ARANGO_EXCEPTION_H
