#include "exception.h"

namespace arango {

exception::exception(const char *message): runtime_error(message)
{
}

exception::exception(const std::string &message): runtime_error(message)
{
}

exception::~exception()
{
}

} // namespace arango
