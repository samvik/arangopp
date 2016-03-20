#include "exception.h"

namespace arango {

exception::exception()
{
}

exception::exception(const char *message): m_message(message)
{
}

exception::exception(const std::string &message): m_message(message)
{
}

exception::~exception()
{
}

const char *exception::what() const noexcept
{
	return m_message.c_str();
}


} // namespace arango
