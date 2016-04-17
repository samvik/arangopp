#ifndef ARANGO_EXCEPTION_H
#define ARANGO_EXCEPTION_H

#include <exception>
#include <string>
#include <stdexcept>

namespace arango {

class exception : public std::runtime_error
{
	public:
		explicit exception(const char* message);
		explicit exception(const std::string &message);
		virtual ~exception();
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
		explicit http_exception(std::string message)
				: exception(message)
		{}

		virtual ~http_exception()
		{}
};

class bad_request_exception : public http_exception
{
	public:
		using http_exception::http_exception;
};

class unauthorized_exception : public http_exception
{
	public:
		using http_exception::http_exception;
};

class not_found_exception : public http_exception
{
	public:
		using http_exception::http_exception;
};

class conflict_exception : public http_exception
{
	public:
		using http_exception::http_exception;
};

} // namespace arango

#endif // ARANGO_EXCEPTION_H
