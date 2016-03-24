#ifndef ARANGO_EXCEPTION_H
#define ARANGO_EXCEPTION_H

#include <exception>
#include <string>

namespace arango {

class exception : public std::exception
{
	public:
		explicit exception();
		explicit exception(const char* message);
		explicit exception(const std::string &message);
		virtual ~exception();
		virtual const char* what() const noexcept;

	private:
		std::string m_message;
};

class query_exception : public exception
{
	public:
		using exception::exception;
};

class connection_exception : public exception
{
	public:
		using exception::exception;
};

class http_exception : public exception
{
	public:
		using exception::exception;
};

class bad_request_exception : public http_exception
{
	public:
		using exception::exception;
};

class unauthorized_exception : public http_exception
{
	public:
		using exception::exception;
};

class not_found_exception : public http_exception
{
	public:
		using exception::exception;
};

class conflict_exception : public http_exception
{
	public:
		using exception::exception;
};

} // namespace arango

#endif // ARANGO_EXCEPTION_H
